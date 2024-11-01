/*
 * Lab #1 : NAND Simulator
 *  - Storage Architecture, SSE3069
 *
 * TA: Jinwoo Jeong, Hyunbin Kang
 * Prof: Dongkun Shin
 * Intelligent Embedded Systems Laboratory
 * Sungkyunkwan University
 * http://nyx.skku.ac.kr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nand.h"

/*
 * define your own data structure for NAND flash implementation
 */

typedef enum {
    PAGE_STATE_EMPTY,
    PAGE_STATE_WRITTEN
} PageState;

typedef struct {
    unsigned char data[32];
    unsigned char spare[4];
    PageState state;
} NANDPage;

typedef struct {
    int nbanks;        // Number of banks
    int nblks;         // Number of blocks per bank
    int npages;        // Number of pages per block
    NANDPage*** pages; // Data storage for NAND flash memory
} NANDFlash;

NANDFlash nand;

/*
 * initialize the NAND flash memory
 * @nbanks: number of bank
 * @nblks: number of blocks per bank
 * @npages: number of pages per block
 *
 * Returns:
 *   NAND_SUCCESS on success
 *   NAND_ERR_INVALID if given dimension is invalid
 */
int nand_init(int nbanks, int nblks, int npages)
{
    if(nbanks <= 0 || nblks <= 0 || npages <= 0){
        return NAND_ERR_INVALID;
    }

    // Initialize NAND flash dimensions
    nand.nbanks = nbanks;
    nand.nblks = nblks;
    nand.npages = npages;

    // Allocate memory for NAND flash data
	nand.pages = (NANDPage***)malloc(nbanks * sizeof(NANDPage**));
	for (int bank=0; bank<nbanks; bank++) {
		nand.pages[bank] = (NANDPage**)malloc(nblks * sizeof(NANDPage*));
		for (int blk = 0; blk < nblks; blk++) {
			nand.pages[bank][blk] = (NANDPage*)malloc(npages * sizeof(NANDPage));
			for (int page = 0; page < npages; page++) {
				memset(&nand.pages[bank][blk][page], 0, sizeof(NANDPage)); // Initialize all pages to zero values
				nand.pages[bank][blk][page].state = PAGE_STATE_EMPTY;
			}
		}
	}

	return NAND_SUCCESS;
}

/*
 * write data and spare into the NAND flash memory page
 *
 * Returns:
 *   NAND_SUCCESS on success
 *   NAND_ERR_INVALID if target flash page address is invalid
 *   NAND_ERR_OVERWRITE if target page is already written
 *   NAND_ERR_POSITION if target page is empty but not the position to be written
 */
int nand_write(int bank, int blk, int page, void *data, void *spare)
{
    if (bank < 0 || bank >= nand.nbanks || blk < 0 || blk >= nand.nblks || page < 0 || page >= nand.npages) {
        return NAND_ERR_INVALID;
    }

    NANDPage *target_page = &nand.pages[bank][blk][page];

    if (target_page->state == PAGE_STATE_EMPTY) {
        if(page > 0){
            NANDPage *check_page = &nand.pages[bank][blk][page - 1];
            if(check_page->state == PAGE_STATE_EMPTY){
                return NAND_ERR_POSITION;
            }
        }
        memcpy(target_page->data, data, sizeof(target_page->data));
        memcpy(target_page->spare, spare, sizeof(target_page->spare));
        target_page->state = PAGE_STATE_WRITTEN;
    }
    else{
        return NAND_ERR_OVERWRITE;
    }

	return NAND_SUCCESS;
}


/*
 * read data and spare from the NAND flash memory page
 *
 * Returns:
 *   NAND_SUCCESS on success
 *   NAND_ERR_INVALID if target flash page address is invalid
 *   NAND_ERR_EMPTY if target page is empty
 */
int nand_read(int bank, int blk, int page, void *data, void *spare)
{
    if (bank < 0 || bank >= nand.nbanks || blk < 0 || blk >= nand.nblks || page < 0 || page >= nand.npages) {
        return NAND_ERR_INVALID;
    }

    NANDPage *target_page = &nand.pages[bank][blk][page];

    if (target_page->state == PAGE_STATE_EMPTY) {
        // Page is empty
        return NAND_ERR_EMPTY;
    }
    else {
        // Page has data, copy it to the provided buffers
        memcpy(data, target_page->data, sizeof(target_page->data));
        memcpy(spare, target_page->spare, sizeof(target_page->spare));
    }
	return NAND_SUCCESS;
}

/*
 * erase the NAND flash memory block
 *
 * Returns:
 *   NAND_SUCCESS on success
 *   NAND_ERR_INVALID if target flash block address is invalid
 *   NAND_ERR_EMPTY if target block is already erased
 */
int nand_erase(int bank, int blk)
{
    if (bank < 0 || bank >= nand.nbanks || blk < 0 || blk >= nand.nblks) {
        return NAND_ERR_INVALID;
    }
    if (nand.pages[bank][blk][0].state == PAGE_STATE_EMPTY){
        return NAND_ERR_EMPTY;
    }
    // Erase the entire block by setting all pages to empty
    for (int page = 0; page < nand.npages; page++) {
        NANDPage *target_page = &nand.pages[bank][blk][page];
        memset(target_page, 0, sizeof(NANDPage)); // Set the page data to all zeros
        target_page->state = PAGE_STATE_EMPTY;
    }
	return NAND_SUCCESS;
}

