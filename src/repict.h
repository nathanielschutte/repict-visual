
#ifndef REPICT_IMPLEMENTATION
#define REPICT_IMPLEMENTATION

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#define KERNEL_MAX 100
#define BYTE_MAX 255

// State flag types
#define REPICT_UNINIT -1	// uninitialized
#define REPICT_NONE 0		// nothing going on
#define REPICT_WORKING 1	// filtering image currently
#define REPICT_READY 2		// image

// Types
typedef unsigned char byte_t;
typedef float kernel_t;


// Buffers and aliases
kernel_t* kernel_working = NULL;				// kernel matrix

static byte_t* image_buf_A = NULL;				// buffer A
static byte_t* image_buf_B = NULL;				// buffer B
static byte_t* image_buf_src = NULL;				// buffer copy of source

static byte_t* image_dest = NULL;				// alias to target destination
static byte_t* image_ready = NULL;				// alias to most current image


// Current state data
static byte_t* m_src_external = NULL;
static size_t m_channels_external;
static int m_state_flag = REPICT_UNINIT;
static size_t m_channels = 3;
static size_t m_width = 0;
static size_t m_height = 0;
static size_t kernel_n = 1;
static size_t kernel_n_last = 0;
static char* m_error_msg[120];					// error code string buffer



// ===== LIBRARY FUNCTIONS =====
// Init, I/O, Clean
bool repict_set_source(byte_t* src, const size_t w, const size_t h, size_t c);
bool repict_add_source(byte_t* src);
void repict_set_buffers(const size_t w, const size_t h, const unsigned c);
byte_t* repict_get_copy();
void repict_copy_back();
void repict_reset();							// reset working image back to source
void repict_clean();							// clean all buffers and data

// Functionality
int repict_convolve(kernel_t* ker, int kn);		// custom kernel of size kn
int repict_gaussian(float sig, int n);			// sigma, n passes

// Access
int repict_get_state();
size_t repict_get_channels();
char* repict_get_error();
// =============================



// ===== INTERNAL FUNCTIONS =====
static void m_copy_image(const byte_t* src, const byte_t* dest, size_t w, size_t h, size_t bpp);
static void m_alloc_image(byte_t* dest, size_t w, size_t h, int bpp);
static void m_alloc_kernel(size_t dim);
static void m_convolve();
static void m_swap_buffers();


// ===== UTILITY FUNCTIONS =====
static float r_get_gaussian(float x, float y, float sig2);


static void m_alloc_image(byte_t* dest, size_t w, size_t h, int bpp) {
	byte_t* img;
	if (dest == NULL) {
		img = (byte_t*) malloc(bpp * w * h);
	}
}

bool repict_set_source(byte_t* src, const size_t w, const size_t h, size_t c) {
	

}





#endif // !REPICT_IMPLEMENTATION
