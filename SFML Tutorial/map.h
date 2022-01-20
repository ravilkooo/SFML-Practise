#pragma once
#include <SFML/Graphics.hpp>
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;

sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0     s f  0                f     s    0",
	"0   sss    0    f                      0",
	"0   sss0  p0                           0",
	"0     f00000        s         s        0",
	"0            f           f             0",
	"00000  s             s            f    0",
	"0             s                        0",
	"0          f            s   p        s 0",
	"0                p      f              0",
	"0s    p                       pf       0",
	"0          sp                          0",
	"0 f                    s          s    0",
	"0            f                         0",
	"0                   0                  0",
	"0   f               0 s        f       0",
	"0      s                               0",
	"0                     f            s   0",
	"0              s                       0",
	"0                        f             0",
	"0      f                               0",
	"0 ff             0   f       f         0",
	"0ppf             0                     0",
	"0ppf      s      0      f      s       0",
	"0000000000000000000000000000000000000000"
};