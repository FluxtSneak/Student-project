virt-install --connect qemu:///system --network network=didiwork --name didi_hyper1 --vcpus=2 --ram 8192 --disk path=images/didi_hyper1.qcow2,bus=virtio,size=6 --graphics vnc --noautoconsole --import
virt-install --connect qemu:///system --network network=didiwork --name didi_hyper2 --vcpus=2 --ram 8192 --disk path=images/didi_hyper2.qcow2,bus=virtio,size=6 --graphics vnc --noautoconsole --import
