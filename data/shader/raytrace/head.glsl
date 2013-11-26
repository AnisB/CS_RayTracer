// Declaration de la version à générer
#version 430

//Destination du rendu
layout(rgba8) uniform image2D renderCanvas;

// Nombre de fils de calcul parrallèles
layout (local_size_x = 16, local_size_y = 16) in;

