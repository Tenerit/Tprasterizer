# Ray Tracing & Ray Marching Algorithm on CPU
Simple ray tracer using sfml library



<p align="center">
  <img src="/docs/readme/ray_tracing.jpg" width="350" height="250" />
</p>


## Install

Windows:
```
git clone https://github.com/Tenerit/Tprasterizer
cd Ray_Tracing_CPU/external
git submodule init SFML
git submodule update

mkdir build
cd build
cmake -S ../SFML/ -B . -G "Unix Makefiles" -DBUILD_SHARED_LIBS=FALSE -DSFML_USE_STATIC_STD_LIBS=TRUE
make

cd ../../example
mkdir build
cd build
cmake -S .. -B . -G "Unix Makefiles" -DBUILD_SHARED_LIBS=FALSE -DSFML_USE_STATIC_STD_LIBS=TRUE
make
RayTracingExample.exe
```

## Controls:

```
   
        - Mouse         - camera rotation
        - Mouse Scroll  - resolution change
        - WASD          - camera forward, left, backward, right movment
        - LShift, LCtr  - camera up, down movment
        - N/M keys      - toggling between two modes (ray/sphere tracing)
        - Z key         - take a screenshot
        - X key         - exit the application
    
```
