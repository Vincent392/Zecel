echo ZecelOS Quick Setup
echo Made by Vincent a.k.a Vincent392 on github and Based IÉ 85520 Class on Discord
echo ===============================================================================
echo updating packages
sudo apt update && apt upgrade
echo [ OK ]
echo Installing gcc
sudo apt install gcc
gcc --version
echo [ OK ]
echo installing gcc build esssential
sudo apt install build-essential
gcc --version
echo [ OK ]
echo installing NASM
sudo apt-get install -y nasm
echo [ OK ]
echo installing QEMU
sudo apt-get install qemu-system
echo [ OK ]
echo Installing Xorriso
sudo apt-get install -y xorriso
echo [ OK ]
