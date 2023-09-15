# texas-holdem-in-cpp

## 1. Download Repo
``` shell
cd /proj
git clone https://github.com/JinLexuan/texas-holdem-in-cpp.git
```

For Linux user, can follow [Docker Guide](/Docker/Docker.md) to build environment.

## 2. Create New Build Folder (Only at First Time)
``` shell
rm -rf build
mkdir build
```

## 3. Compile
``` shell
cd build
cmake ..
cmake -j32
```

## 4. Run Code (inside `bin` folder)
```
./texas
```

## 5. Run Test
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

## 6. Run GUI
Compile
``` shell
cd build
cmake -DTH_GUI=on ..
make -j32
```

Run Test (inside `bin` folder)
``` shell
./texas_gui
```

## Add Git Hooks
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