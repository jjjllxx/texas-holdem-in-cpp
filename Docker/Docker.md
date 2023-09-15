# Setup docker

*The following commands are run in your local PC*

## Install Docker (Ubuntu)

1. Install Docker and its dependencies:
``` bash 
sudo apt update
sudo apt install docker.io
```

2. Start the Docker service and enable it to start on boot:
``` bash
sudo systemctl start docker
sudo systemctl enable docker
```

3. Verify that Docker is installed and running by running a simple command like:
``` bash
docker --version
```

Before doing the following steps, it is recommanded to go trhough all the files in `Docker` folder, focusing on file paths, in case of unintended errors.
## Setup environment

*This is a 1 time step*

1. In your home directory, open `.bashrc` and add `source /proj/texas-holdem-in-cpp/Docker/dock-setup.sh` to the bottom.
2. You may need to add execute permissions to the script (`chmod +x /proj/texas-holdem-in-cpp/Docker/dock-setup.sh`)
3. Run `dock thd` in terminal to enter the docker container. (thd means texas hold'em develop)

There are more convenient functions in the script you can refer to.

## Build image

*You can set your own docker container name. Change `container_name` in `docker-compose.yml`.*

**WARNING! If you set a container name that already exists, its container will be overwritten! You can run `dockc` to check existing container names.**

```bash
cd /proj/texas-holdem-in-cpp/Docker
sudo apt-get install docker-compose-plugin
dockb thd
```

---

## Enter docker container

```bash
dock thd
```

The default path in docker should be `/proj/texas-holdem-in-cpp/build`.  

Then the following steps can refer to [README](../README.md). The commands should be run in the docker container.