# tpedia 
# Copyright (C) 2026  float314

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# This is the installation script for tpedia. It will install tpedia from source.
# and build it. 

echo "Installing tpedia..."

echo "Build Mode: from source" 

echo "Installing dependencies..."
sudo apt update
sudo apt install -y git cmake ninja-build build-essential 

git clone https://github.com/float314/tpedia.git tmp_tpedix

cd tmp_tpedix
cmake -S . -B build -G Ninja -DCMAKE_UNITY_BUILD=ON
cmake --build build --config Release
cd build
sudo cmake --install . --prefix /usr/local

cd ..
rm -rf tmp_tpedix

echo "Installation complete!"

echo "tpedia  Copyright (C) 2026  float314"
echo "This program comes with ABSOLUTELY NO WARRANTY; for details goto settings -> about."
echo "This is free software, and you are welcome to redistribute it"
echo "under certain conditions; see settings -> about for details."

