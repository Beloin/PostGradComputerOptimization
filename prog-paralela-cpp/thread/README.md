# Dreadhot 

Thread 01

mt_01.lock();
mt_02.lock();

Thread 02

mt_02.lock();
mt_01.lock();


Isso gerará consequentemente um dreadjtop
