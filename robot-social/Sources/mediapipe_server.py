
# Author : Florent Didion
# Version : 1.0.0
# Date : 25.06.2023
# /!\ The code is an adaptation of this opencv project : https://github.com/spmallick/learnopencv/blob/master/Posture-analysis-system-using-MediaPipe-Pose/human_posture_analysis_video.py


import math
import socket
import threading
import pickle
import ast
import pysftp
import mediapipe as mp
import cv2


def getAngle(p1, p2, p3):
    """
    compute the angle formed by vector p1->p2 and p3->p2, and returns it in degrees
    """

    # define vector p1->p2 and p3->p2
    vector1_x = p1[0] - p2[0]
    vector1_y = p1[1] - p2[1]
    vector2_x = p3[0] - p2[0]
    vector2_y = p3[1] - p2[1]

    # compute the angle using scalar prod and lenght of the vector
    scalar_product = vector1_x * vector2_x + vector1_y * vector2_y
    vector_lenght = math.sqrt(vector1_x ** 2 + vector1_y ** 2) * math.sqrt(vector2_x ** 2 + vector2_y ** 2)
    
    # checking for null vector
    if vector_lenght != 0:
        theta = math.acos(scalar_product / vector_lenght)
        degree = int(math.degrees(theta))
        return degree
    else:
        return None


def analyse_video(file_name, parameters):
      
    # Video metadatas
    cap = cv2.VideoCapture(file_name)
    fps = int(cap.get(cv2.CAP_PROP_FPS))
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    frame_size = (width, height) 

    # Video writer
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    video_output = cv2.VideoWriter(file_name.replace(".avi","_out.mp4"), fourcc, fps, frame_size)   

    # Init mediapipe task
    mp_pose = mp.solutions.pose
    pose = mp_pose.Pose()  

    # init angles values and if the angle should increase or decrease
    success, image = cap.read()
    if not success:
        print("Can't init evaluation values, return error")
        return "Error can't get landmarks on video, please try again"
    # Process the image.
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    keypoints = pose.process(image)
    lm = keypoints.pose_landmarks
    # Init angle values (angle value, should increase or decrease) increase = 0, decrease = 1
    angles =[None for param in parameters]
    try:
        for i in range(len(angles)) :
            p1 = (int(lm.landmark[parameters[i][1]].x * width),int(lm.landmark[parameters[i][1]].y * height))
            p2 = (int(lm.landmark[parameters[i][2]].x * width),int(lm.landmark[parameters[i][2]].y * height))
            p3 = (int(lm.landmark[parameters[i][3]].x * width),int(lm.landmark[parameters[i][3]].y * height))
            angle = getAngle(p1,p2,p3)
            way = 0
            if angle > parameters[i][0]:
                way = 1
            angles[i] = [angle, way]
    except:
        print ("Can't get landmarks on the first frame, return error")
        return "Error can't get landmarks on video, please try again"

    # Analyse video
    while cap.isOpened():
        # Capture frames.
        success, image = cap.read()
        if not success:
            print("Null.Frames")
            break       

        # Convert the BGR image to RGB.
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

        # Process the image.
        keypoints = pose.process(image)

        # Convert the image back to BGR.
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        # Use lm  as representative of the following method.        
        lm = keypoints.pose_landmarks
        
        # Acquire the landmark coordinates for each point in the parameters list      
        try:
            for i in range(len(parameters)):
                p1 = (int(lm.landmark[parameters[i][1]].x * width),int(lm.landmark[parameters[i][1]].y * height))
                p2 = (int(lm.landmark[parameters[i][2]].x * width),int(lm.landmark[parameters[i][2]].y * height))
                p3 = (int(lm.landmark[parameters[i][3]].x * width),int(lm.landmark[parameters[i][3]].y * height))

                # Draw points p1 p2 p3
                cv2.circle(image, (p1[0], p1[1]), 7, (0, 255, 255), -1)
                cv2.circle(image, (p2[0], p2[1]), 7, (0, 255, 255), -1)
                cv2.circle(image, (p3[0], p3[1]), 7, (0, 255, 255), -1)

                # Draw lines p1->p2 and p3->p2
                cv2.line(image, (p1[0], p1[1]), (p2[0], p2[1]), (255, 127, 0), 4)
                cv2.line(image, (p3[0], p3[1]), (p2[0], p2[1]), (255, 127, 0), 4)

                # Check for angle value update
                new_angle = getAngle(p1,p2,p3)
                if angles[i][0]< new_angle and angles[i][1] == 0: angles[i][0] = new_angle
                if angles[i][0]> new_angle and angles[i][1] == 1: angles[i][0] = new_angle
                
        except:
            print("Can't get landmarks")
    
        # Write frames.
        video_output.write(image)
    
    cap.release()
    res=[]
    for i in range(len(parameters)):
        res.append(angles[i][0]*100/parameters[i][0])
        
    return res

def download_video_FTP(client_ip):
  # FTP server parameters
  print(client_ip)
  ftp_user = "nao"
  ftp_password = "labo"
  filename_out =  "/home/labo/videos/" + str(client_ip) + "_video.avi"
  filename_in = "/data/home/nao/recordings/cameras/video.avi"

  # Connect to Nao with sftp
  with pysftp.Connection(host=client_ip, username=ftp_user, password=ftp_password) as sftp:
    print("Connection successfully established ... ")
    # Download file
    sftp.get(filename_in, filename_out)

  print("Le fichier", filename_in,filename_out, "a été téléchargé avec succès.")
  return filename_out


def handle_client(client_socket, client_address):

    # Receive evaluation parameters and convert it to a proper python list
    parameters = pickle.loads(client_socket.recv(1024))
    parameters = ast.literal_eval(parameters)
    parameters = [(int(a), int(b), int(c), int(d)) for a, b, c, d in parameters]

    # Download the video on the robot
    video_name = download_video_FTP(client_address[0])

    # Analyse poses on the video
    result = analyse_video(video_name, parameters)
    
    # Send result to Nao
    client_socket.sendall(pickle.dumps(result))   

    # Close connection
    client_socket.close()
    print("Client disconnected:", client_address)

def start_server(host, port):
    # Create socket for the server
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print("Server started on", host, "port", port)

    while True:
        # Waiting for client to connect
        client_socket, client_address = server_socket.accept()
        print("Client connected:", client_address)

        # Handle client in a new thread
        client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
        client_thread.start()

# Server configuration
HOST = '192.168.0.5'  # IP
PORT = 8081  # listening port 

# Démarrage du serveur
start_server(HOST, PORT)

