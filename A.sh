###
 # @Author       : Rainer-seventeen 1652018592@qq.com
 # @Date         : 2024-04-07 21:05:56
 # @LastEditors  : Rainer-seventeen
 # @LastEditTime : 2024-04-09 10:41:16
### 

rm -fr ./build
cmake -B build
make -C build/ -j4
echo " "
echo " "
echo "=============================RUNNING================================"


build/run