## The actual settings of the bots are

cnc domain name= cnc.lab.com
scanner.lab.com
dns 8.8.8.8

# Docker

## Build image

In the root folder, execute:

```bash
sudo docker build -t mirai_lab --progress=plain .
```

## run the container with interactive shell

Warning, the internet access of the container has to be removed somehow
```bash
sudo docker run -it mirai_lab
```

## Using docker compose

docker-compose run <service_name>