#!/bin/bash

sudo apt-get update && sudo apt-get upgrade -y

sudo apt-get install libxcb-xinerama0 -y

cd $HOME

wget "https://dl.walletbuilders.com/download?customer=6d253575d412609f881684035cbcf5dc3ffa19a127ae4b4e8a&filename=bitcoins-qt-linux.tar.gz" -O bitcoins-qt-linux.tar.gz

mkdir $HOME/Desktop/Bitcoins

tar -xzvf bitcoins-qt-linux.tar.gz --directory $HOME/Desktop/Bitcoins

mkdir $HOME/.bitcoins

cat << EOF > $HOME/.bitcoins/bitcoins.conf
rpcuser=rpc_bitcoins
rpcpassword=dR2oBQ3K1zYMZQtJFZeAerhWxaJ5Lqeq9J2
rpcbind=127.0.0.1
rpcallowip=127.0.0.1
listen=1
server=1
addnode=node3.walletbuilders.com
EOF

cat << EOF > $HOME/Desktop/Bitcoins/start_wallet.sh
#!/bin/bash
SCRIPT_PATH=\`pwd\`;
cd \$SCRIPT_PATH
./bitcoins-qt
EOF

chmod +x $HOME/Desktop/Bitcoins/start_wallet.sh

cat << EOF > $HOME/Desktop/Bitcoins/mine.sh
#!/bin/bash
SCRIPT_PATH=\`pwd\`;
cd \$SCRIPT_PATH
while :
do
./bitcoins-cli generatetoaddress 1 \$(./bitcoins-cli getnewaddress)
done
EOF

chmod +x $HOME/Desktop/Bitcoins/mine.sh
    
exec $HOME/Desktop/Bitcoins/bitcoins-qt &

sleep 15

exec $HOME/Desktop/Bitcoins/bitcoins-cli -named createwallet wallet_name="" &
    
sleep 15

cd $HOME/Desktop/Bitcoins/

clear

exec $HOME/Desktop/Bitcoins/mine.sh