ROOT_DIR=$(pwd)

sudo rosdep init
rosdep update

for PACKAGE in $(colcon list -t | cut -f2); do
  cd $ROOT_DIR/$PACKAGE || continue
  bloom-generate rosdebian || exit $?
  fakeroot debian/rules binary -j8 || exit $?
  rm -rf debian .obj*
done
