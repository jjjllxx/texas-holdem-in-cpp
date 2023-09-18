#!/bin/bash

dock()
{
  if [ "$#" -eq 0 ]; then
    echo "Usage: dock [container name or container ID]"
    echo "Example Usage: dock thd"
  elif [ "$#" -eq 1 ]; then
    docker exec -it $1 /bin/bash 
  else
    echo "Invalid number of arguments"
  fi
}

# remove containers
dockrc() { docker stop $@; docker rm $@; }

# check containers 
dockc() { docker ps -a; }

# remove images
dockri() { docker rmi $@; }

# check images
docki() { docker images; }

# build and run containers
dockb() { docker compose up -d --build $@; }

echo "Docker environment setup successfully"
