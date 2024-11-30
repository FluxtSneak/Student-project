pvcreate /dev/sda /dev/sdb
vgcreate storage_lvm /dev/sda /dev/sdb
lvcreate -n storage_lvm_didi -l 100%VG storage_lvm
mkfs -t ext4 /dev/mapper/storage_lvm-storage_lvm_didi
mkdir /mnt/storage
echo '/mnt/storage  192.168.40.130(rw,sync,no_subtree_check)' >> /etc/exports
echo '/mnt/storage  192.168.40.131(rw,sync,no_subtree_check)' >> /etc/exports
mount /dev/mapper/storage_lvm-storage_lvm_didi /mnt/storage
exportfs -a
systemctl restart nfs-kernel-server
chmod 777 /mnt/storage
chown -R nobody:nogroup /mnt/storage
