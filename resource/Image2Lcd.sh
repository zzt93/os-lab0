#!/bin/bash

myread() {
	# $1 - offset in bytes to start
	# $2 - length in bytes to read
	# $3 - dump format
	# $4 - file

	# fill in the blank to implement the function of reading $2 bytes starting at $1
	hexdump -s $1 -n $2 -v -e $3 $4
}

magic=$(myread 0 2 '"%c"' $1)
if [[ $magic != "BM" ]]
then
	echo "$1 is not a bmp file."
	exit 1
fi

# fill in the blank to read the bpp field from the file, which is stored at the offset 0x1c, with 2-byte length
bbp=$(myread 0x1c 2 '"%d"' $1)
if [[ $bbp != 8 ]]			# modify this condition to check whether bbp has value 8. If not, print a message and exit
then
	echo "$1 is not a 256-color bmp file."
	exit 1
fi

BMP_header_size=14
pixel_offset=$(myread 0xa 4 '"%d"' $1)
DIB_header_size=$(myread $BMP_header_size 4 '"%d"' $1)

palette_offset=$(($BMP_header_size + $DIB_header_size))
palette_size=0
# fill in the blank to calculate the size of palette according to the information above
# running with example.bmp, this value should be 1024
palette_size=$(($pixel_offset - $palette_offset))


# fill in the blank to implement the function of reading $palette_size bytes starting at $palette_offset
# running with example.bmp, this command will output an 256-line array, with 4 elements per line. The first line will be "0x00, 0x00, 0x00, 0x00". The last line will be "0xff, 0xff, 0xff, 0x00"
file=$(basename "$1")
extension="${file##*.}"
file="${file%.*}"
file+="_palette"

xxd -c 4 -s $palette_offset -l $palette_size -i $1 > $file

width=$(myread 0x12 4 '"%d"' $1)
height=$(myread 0x16 4 '"%d"' $1)

pad_width=$(( ($width + 3) / 4 * 4))


# fill in the 4 blanks to implement:
# (1) output $pad_width pixels per line
# (2) start from offset $pixel_offset
# (3) use regular expression to filter padding bytes
# (4) output $width pixels per line (this is the same as (1) )

# running with example.bmp, the output of this command should be
#	0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x13, 0x15, 0x0a, 0x00, 0x00, 0x00, 0x00,
#	0x00, 0x00, 0x00, 0x0a, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x1d, 0x0b, 0x0b, 0x00,
#	0x00, 0x00, 0x00, 0x6f, 0x77, 0x77, 0x77, 0x77, 0x6f, 0x77, 0x77, 0x6f, 0x13,
#	0x00, 0x00, 0x1c, 0xbf, 0xbf, 0xbf, 0xbf, 0x6f, 0x77, 0xbf, 0x77, 0x6f, 0x1d,
#	0x00, 0x00, 0x77, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x77, 0x6f, 0x0b,
#	0x00, 0x5c, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x26, 0x0a,
#	0x00, 0x77, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x77, 0x1d, 0x00,
#	0x13, 0x6f, 0x77, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x66, 0x1c, 0x00,
#	0x6f, 0x77, 0x77, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x77, 0x26, 0x00, 0x00,
#	0x25, 0x6f, 0x77, 0x77, 0x6f, 0x77, 0x77, 0x6f, 0x6f, 0x1d, 0x13, 0x00, 0x00,
#	0x00, 0x00, 0x1c, 0x66, 0x6f, 0x6f, 0x6f, 0x77, 0x6f, 0x0c, 0x00, 0x00, 0x00,
#	0x00, 0x00, 0x00, 0x00, 0x0a, 0x0a, 0x0a, 0x1d, 0x1d, 0x0a, 0x00, 0x00, 0x00
gwidth=$((2 * $width))
#echo $gwidth
#str=$(xxd -l $pad_width -s $pixel_offset -ps $1 | tac )
#echo "${str::$gwidth}" | xxd -l $width

filename=$(basename "$1")
extension="${filename##*.}"
filename="${filename%.*}"
filename+="_bmp"

#echo $filename
echo "unsigned char $filename [] = {" > $filename
xxd -c $pad_width -s $pixel_offset -ps $1 | tac | grep -o ".\{$gwidth\}" | xxd -r -ps | xxd -c $width -i >> $filename
echo "};" >> $filename

