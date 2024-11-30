res=$(virsh --connect qemu:///system net-list | grep "didiwork" | wc -l )
if [ $res -lt 1 ]
then
    virsh --connect qemu:///system net-create xml/didiwork.xml 
fi
