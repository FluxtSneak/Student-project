virt-install --connect qemu:///system --network network=didiwork --name didi_storage --vcpus=2 --ram 8192 --disk path=images/didi_storage.qcow2,bus=virtio,size=6 --disk path=images/storage1.img,size=10 --disk path=images/storage2.img,size=10 --graphics vnc --noautoconsole --import
