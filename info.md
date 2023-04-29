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

## run the container (alone) with interactive shell

Warning, as is, the container has internet access, do not run the bot.
```bash
sudo docker run -it mirai_lab
```

## Using docker compose

```bash
sudo docker compose run cnc
```
