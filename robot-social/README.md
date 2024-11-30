This repo contains elements needed to give nao the ability to analyse movements reproduction.

The Mouvements repo contains a Choregraph library where you will find 3 exercices and a template to create your own exercises.
We run the mediapipe_server on a Nvidia Jetson nano 4GB, but it can run on any machine powerfull enough to run mediapipe.

Communication between Nao and the server is made through python sockets. This project currently contains NO SECURITY, use it at your own risks.