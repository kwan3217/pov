#!/bin/sh
rm -rfv MahorabaA MahroabaA.iso
rm -rfv Mahoraba
./MakeMenu.sh
dvdauthor -x MahorabaA.xml 
mkisofs -dvd -o MahorabaA.iso MahorabaA
echo "Done!"
