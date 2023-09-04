# texas-holdem-in-cpp

## 1. Download Repo
``` shell
git clone https://github.com/JinLexuan/texas-holdem-in-cpp.git
```

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

## 5. Enable Test
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

## Add Git Hooks
``` shell
cd .git/hooks
ln -s ../../Scripts/Git/commit-msg commit-msg
ln -s ../../Scripts/Git/prepare-commit-msg prepare-commit-msg
```