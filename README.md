# texas-holdem-in-cpp

## 1. Download Repo
``` shell
cd /proj
git clone https://github.com/jjjllxx/texas-holdem-in-cpp.git
```

## 2. Create New Build Folder (Only at First Time)
``` shell
rm -rf build
mkdir build
```

## 3. Create Docker (optional for Linux user)
For this step, it is assumed `texas-holdem-in-cpp` folder is in `proj` folder, otherwise please change the path according to your computer.  
The name of docker image and container can also be changed if you want.
### Create Docker Image
``` bash
cd /proj/texas-holdem-in-cpp
docker build -t thd:1.0 -f thd.Dockerfile .
```

### Create Docker Container
``` bash
docker run -it \
    --name thd \
    --workdir /proj/texas-holdem-in-cpp/build \
    --volume /proj/texas-holdem-in-cpp:/proj/texas-holdem-in-cpp \
    --network host \
    --ipc host \
    --pid host \
    --privileged \
    --env DISPLAY=${DISPLAY} \
    thd:1.0
```

### Enter Docker Container
``` bash
docker start thd
docker exec -it thd /bin/bash 
```

For this step, it is assumed `texas-holdem-in-cpp` folder is in `proj` folder, otherwise please change the path according to your computer.  
## 4. Compile
``` shell
cd build
cmake ..
cmake -j32
```

## 5. Run Texas Hold'em (inside `bin` folder)
```
./texas
```

## 6. Unit Tests
Compile
``` shell
cd build
cmake -DTH_TEST=on ..
make -j32
```

Run Test (inside `bin` folder)
``` shell
./texas_test
```

Run a Subset of the Tests
``` shell
./texas_test --gtest_filter=`filter condition`
```
For filter condition, you can refer to [official document](http://google.github.io/googletest/advanced.html#running-a-subset-of-the-tests) or ask Chatgpt.

## 7. GUI
Compile
``` shell
cd build
cmake -DTH_GUI=on ..
make -j32
```

Run GUI (inside `bin` folder)
``` shell
./texas_gui
```

## 8. Add Git Hooks
1. Give executable permissions to the hook files: 
``` shell
cd Scripts/Git
chmod +x *
```

2. Create a link for the hooks: 
``` shell
cd ../../.git/hooks
ln -s ../../Scripts/Git/* .
```
