#!/usr/bin/env python3

import requests
import jinja2
import json
import sys
#find the project uid
PROJECTS_URL="https://gns3.hepiapp.ch/v2/projects"
pjs=json.loads(requests.get(PROJECTS_URL).content)
id='a'
for pj in pjs :
    if sys.argv[1]==pj['filename']:
        id=pj['project_id']
if id=='a':
    print("Project not found")
    exit()

#get project infos + machines
PROJECTS_NODES_URL=PROJECTS_URL+'/'+id+'/nodes'
data=requests.get(PROJECTS_NODES_URL)
data_json=json.loads(data.content)

#use template to generate new config file
env = jinja2.Environment(loader=jinja2.FileSystemLoader("/home/flo/Desktop/tp2"))
template = env.get_template('config_template.txt')
f=open('/home/flo/.ssh/config.d/config.ssh', 'w')
f.close()
for elem in data_json:
    if elem['console_type']!='none':
        with open('/home/flo/.ssh/config.d/config.ssh', 'a') as f:
            f.write(template.render(elem=elem))


def usage():
    print(f"{sys.argv[0]} PROJECT_NAME")


#change hostnames
f=open('/home/flo/.ssh/config.d/config.ssh', 'r')



    