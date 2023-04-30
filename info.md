## The actual settings of the bots are

cnc domain name= cnc.mirai-lab
scanner cnc.mirai-lab
dns 127.0.0.11

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
```bash
sudo docker compose run bot
```
```bash
sudo docker compose run attacker
```