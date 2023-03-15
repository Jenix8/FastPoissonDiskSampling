# Fast Poisson Disk Sampling

* [Paper](https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)

This code can generate samples from a blue noise distribution in O(N) time.
The above paper says that his algorithm can be implemented in arbitrary dimension,
but this code is only implemented in 2D yet.  

## What to see
    - FPDS/Renderer.cpp
    - FPDS/sim.cpp
    - FPDS/sim.h

# result

<img src = "https://user-images.githubusercontent.com/108937571/225290702-fc9306fc-05b4-4486-8481-a9d57c2564d9.png" width = "30%" height = "30%">

<img src = "https://user-images.githubusercontent.com/108937571/225290705-ec369eab-4e34-45ad-a358-a2be2da76d4d.png" width = "30%" height = "30%">

<img src = "https://user-images.githubusercontent.com/108937571/225290710-0af7c3c5-9fc8-48b1-9e07-4bfbf4aa6d24.png" width = "30%" height = "30%">  
  
there is no pair of points such that the distance between two is less than $r$ set up first. 
(in this case, the width and height are $512$ pixels, and $r = 16$.)



