#include "common.h"


//#define DEBUG

/* The following code is from Iodev.org, modified for integer */
#define filterWidth 5
#define filterHeight 5
#define imageWidth 64
#define imageHeight 64

//declare image buffers 
unsigned int conv5_image[imageWidth*imageHeight]; 
unsigned int conv5_result[imageWidth*imageHeight];


inline int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

inline int min(int a, int b)
{
	if (a < b) return a;
	else return b;
}

int filter5x5[filterWidth][filterHeight] =
{
     32, 32, 32, 32, 32,
     32, 32, 32, 32, 32,
     32, 32, 32, 32, 32,
     32, 32, 32, 32, 32,
     32, 32, 32, 32, 32
};


#if USE_FACTOR
int factor = 256;
int bias = 0;
#endif

NOP(){}
char strbuf[12];
int main()
{
    unsigned int* framebuffer = conv5_result;
    unsigned int* image = conv5_image;
    int timerread;
	//puts("convolution starting\n");
	//init_vga();

    int i, x, y, filterX, filterY, imageX, imageY;


#ifdef DEBUG
    int runs;
#endif


	NOP();
	/* First write a test screen */
/*
	for (i = 0; i < 640*160; i++)
	{
		image[i] = 0x00FF0000 - ((((i%640)/3)&0xff)<<16);
	}

	for (; i < 640*320; i++)
	{
		image[i] = 0x0000FF00 - ((((i%640)/3)&0xff)<<8);
	}

	for (; i < 640*480; i++)
	{
		image[i] = 0x000000FF - (((i%640)/3)&0xff);
	}
*/

	//Clear the output image

//	#pragma unroll(4)
	for (i = 0; i < (imageWidth*imageHeight); i++)
		framebuffer[i] = 0;

#ifdef DEBUG
    for (runs = 0; runs < 2; runs++){
#endif
    //apply the filter
    for(y = filterHeight/2; y < imageHeight-(filterHeight/2); y++)
    for(x = filterWidth /2; x < imageWidth -(filterWidth /2); x++)
    {
        int red = 0, green = 0, blue = 0;

        //multiply every value of the filter with corresponding image pixel

        for(filterX = 0; filterX < filterWidth; filterX++)
//        #pragma unroll(4)
        for(filterY = 0; filterY < filterHeight; filterY++)
        {
//            imageX = (x - filterWidth / 2 + filterX + imageWidth) % imageWidth;
//            imageY = (y - filterHeight / 2 + filterY + imageHeight) % imageHeight;
            imageX = (x - filterWidth / 2 + filterX);// % imageWidth;
            imageY = (y - filterHeight / 2 + filterY);// % imageHeight;

            red   += (((signed int)((image[imageX + (imageY*imageWidth)]>>16)&0xFF)) * filter5x5[filterX][filterY])/256;
            green += (((signed int)((image[imageX + (imageY*imageWidth)]>> 8)&0xFF)) * filter5x5[filterX][filterY])/256;
            blue  +=  (((signed int)(image[imageX + (imageY*imageWidth)]     &0xFF)) * filter5x5[filterX][filterY])/256;

#ifdef DEBUG
if(runs){
            puts("Old RGB:\n");
            tohex(strbuf, ((image[imageX + (imageY*imageWidth)]>>16)&0xFF));
            puts(strbuf);
            tohex(strbuf, ((image[imageX + (imageY*imageWidth)]>> 8)&0xFF));
            puts(strbuf);
            tohex(strbuf, (image[imageX + (imageY*imageWidth)]&0xFF));
            puts(strbuf);

            puts("RGB additions:\n");
            tohex(strbuf, red);
            puts(strbuf);
            tohex(strbuf, green);
            puts(strbuf);
            tohex(strbuf, blue);
            puts(strbuf);
}
#endif

        }
#ifdef DEBUG
if(runs){
        puts("RGB values:\n");
        tohex(strbuf, red);
        puts(strbuf);
        tohex(strbuf, green);
        puts(strbuf);
        tohex(strbuf, blue);
        puts(strbuf);
}
#endif

#if USE_FACTOR
        //truncate values smaller than zero and larger than 255
        framebuffer[x][y] = min(max(int(factor * red + bias), 0), 255)<<16
		| min(max(int(factor * green + bias), 0), 255)<<8
        | min(max(int(factor * blue + bias), 0), 255);
#else
        //truncate values smaller than zero and larger than 255
        framebuffer[(y*imageWidth)+x] = min(max(red, 0), 255)<<16
        | min(max(green, 0), 255)<<8
        | min(max(blue, 0), 255);
#endif //USE_FACTOR
    }
#ifdef DEBUG
    } //runs
#endif


	puts("Convolution 5x5: success\n");

    return 0;
}

