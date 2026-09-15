/** @file lfrfid_hid_format.h
 *
 * The well-known Wiegand formats carried on HID Proximity cards, HID's own and other
 * makers' (AMAG S10401, Continental C10202), read out of and packed into the 44-bit field that the
 * firmware's Generic HIDProx protocol carries as its data.
 */

#pragma once

#include <furi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LfRfidHidFormat LfRfidHidFormat;

/** Number of formats known */
#define LFRFID_HID_FORMAT_COUNT (6)

/** A format by index, NULL past the end. */
const LfRfidHidFormat* lfrfid_hid_format_get(size_t index);

/** The format's name as shown to the user, e.g. "H10304". */
const char* lfrfid_hid_format_get_name(const LfRfidHidFormat* format);

/** Whose format it is, "HID" or another maker's name, to go before the name in a list. */
const char* lfrfid_hid_format_get_manufacturer(const LfRfidHidFormat* format);

/** Whether the format carries a facility code. */
bool lfrfid_hid_format_has_facility_code(const LfRfidHidFormat* format);

/** Largest facility code the format holds, 0 for a format without one. */
uint64_t lfrfid_hid_format_get_facility_code_max(const LfRfidHidFormat* format);

/** Largest card number the format holds. */
uint64_t lfrfid_hid_format_get_card_number_max(const LfRfidHidFormat* format);

/** Pack a facility code and card number, each masked to the format's width, into the 6
 * bytes of Generic HIDProx data. Any other bits the format names (the C10202 issue level)
 * are left 0, which is how the cards are sold. */
void lfrfid_hid_format_encode(
    const LfRfidHidFormat* format,
    uint64_t fc,
    uint64_t cn,
    uint8_t* data);

/** Append a "NAME: FC x Card y" line to result for every format the 6 bytes of Generic
 * HIDProx data match, with " Issue z" on the end when the format names an issue level and
 * the card carries one other than 0. */
void lfrfid_hid_format_render(const uint8_t* data, FuriString* result);

#ifdef __cplusplus
}
#endif
