

>running fetch
```sh

sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libcjson-dev


 gcc -o fetch fetch.c -lcurl -lcjson
```


> running binance
```sh
gcc -o buy  buy.c -lcurl -lcjson -lssl -lcrypto

```




