
mov_scanner

Put your movie in /data/movies directly.
You can use all size of movie you want.

DO NOT use subdirectory

	OK   /data/movies/abc.mov
	x      /data/movies/big/abc.mov


Keyboard control{

d 			change direction of movie
LR arrow		change threshold
Shift + LR arrow	change indicator speed
1, 2, 3, … 0		change movie file inside of /data/movies
m			show/hide movie
space			stop movie

!New!
#			switch dot/line scan
A			add dot scan point

}

Mode

Osc global setting{
	out ip address	localhost
	out port	12345
}

line scan mode
{
	osc format
	message		/ch/id value	
	ch range	1 ~ 8
	id range	1 ~ 10
	value range	0 ~ 255

	midi format
	midi ch range	1 ~ 32
	cc range 	102 ~ 112
	value		0 ~ 255
}


dot scan mode{
	message		/ch value
	ch range	1 ~ …
	value range	0 ~ 255

	midi format
	midi ch range	1 ~ …
	cc range 	102
	value		0 ~ 255
}

Update	rev1.3	14.9.2014
