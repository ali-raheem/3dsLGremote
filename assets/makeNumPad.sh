#!/bin/bash
convert tile_0051.png tile_0052.png tile_0053.png +append row0.png
convert tile_0054.png tile_0055.png tile_0056.png +append row1.png
convert tile_0057.png tile_0058.png tile_0059.png +append row2.png
convert tile_0001.png tile_0060.png tile_0001.png +append row3.png
convert row*.png -append numpad.png

