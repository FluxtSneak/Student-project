mkdir images
cd images
virt-builder debian-11 -o didi_storage.qcow2 --hostname storage --format qcow2 --root-password password:root --edit '/etc/default/keyboard: s/^XKBLAYOUT=.*/XKBLAYOUT="ch"/' --install 'lvm2' --install 'nfs-kernel-server' --firstboot-command 'ip addr add 192.168.40.129/24 dev ens3' --firstboot-command 'ip link set ens3 up' 
virt-builder debian-11 -o didi_hyper1.qcow2 --hostname hyper1 --format qcow2 --root-password password:root --edit '/etc/default/keyboard: s/^XKBLAYOUT=.*/XKBLAYOUT="ch"/' --install 'libguestfs-tools' --install 'libvirt0' --install 'qemu-kvm' --install 'libvirt-daemon-system' --install 'nfs-common' --firstboot-command 'mount 192.168.40.129:/mnt/storage /var/lib/libvirt/images/' --firstboot-command 'ip addr add 192.168.40.130/24 dev ens3' --firstboot-command 'ip link set ens3 up'
virt-builder debian-11 -o didi_hyper2.qcow2 --hostname hyper2 --format qcow2 --root-password password:root --edit '/etc/default/keyboard: s/^XKBLAYOUT=.*/XKBLAYOUT="ch"/' --install 'libguestfs-tools' --install 'libvirt0' --install 'qemu-kvm' --install 'libvirt-daemon-system' --install 'nfs-common'  --firstboot-command 'mount 192.168.40.129:/mnt/storage /var/lib/libvirt/images/' --firstboot-command 'ip addr add 192.168.40.131/24 dev ens3' --firstboot-command 'ip link set ens3 up'
qemu-img create storage1.img -f qcow2 10G
qemu-img create storage2.img -f qcow2 10G
cd ..
