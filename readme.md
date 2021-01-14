### pacman-3d
#### this is an attempt to revive a college team project


#### contributors:
[demon36](https://github.com/demon36), [sarao19](https://github.com/sarao19), nouran el sherif

#### todo:
- [x] port to linux
- [x] get the gameplay barely working
- [ ] fix missing resource directory
- [ ] fix maze model
- [ ] fix ghosts movements
- [ ] fix audio on linux
- [ ] massive code cleanup
- [ ] add cross platform build configuration

#### nasty way to get it working on linux:
```sh
apt-get install libglm-dev libglew-dev libglfw3-dev freeglut3-dev libassimp-dev
git clone https://github.com/demon36/pacman-3d.git
cd pacman-3d
make
cd src
../bin/64/debug/pacman-3d
```
