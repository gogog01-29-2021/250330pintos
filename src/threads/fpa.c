#include "threads/fpa.h"
 // fpa = "fixed-point arithmetic"
 
 /* Convert integer to fpa */
 fpa int_to_fpa(int n) {
     // not implemented yet
     return n * F;
 }
 
 /* Convert fpa to integer (truncates) */
 int fpa_to_int(fpa x) {
     // not implemented yet
     return x / F;
 }
 
 /* Convert fpa to nearest integer */
 int fpa_to_nearest_int(fpa x) {
     // not implemented yet
     return (x >= 0) ? ((x + F/2) / F) : ((x - F/2) / F);
 }
 
 /* Add two fpa values */
 fpa fpa_add(fpa x, fpa y) {
     // not implemented yet
     return x + y;
 }
 
 /* Subtract fpa y from fpa x */
 fpa fpa_sub(fpa x, fpa y) {
     // not implemented yet
     return x - y;
 }
 
 /* Add integer to fpa */
 fpa fpa_add_int(fpa x, int i) {
     // not implemented yet
     return x + int_to_fpa(i);
 }
 
 /* Subtract integer from fpa */
 fpa fpa_sub_int(fpa x, int i) {
     // not implemented yet
     return x - int_to_fpa(i);
 }
 
 /* Multiply two fpa values */
 fpa fpa_mul(fpa x, fpa y) {
     // not implemented yet
     return ((int64_t)x) * y / F;
 }
 
 /* Multiply fpa by integer */
 fpa fpa_mul_by_int(fpa x, int i) {
     // not implemented yet
     return x * i;
 }
 
 /* Divide fpa x by fpa y */
 fpa fpa_div(fpa x, fpa y) {
     // not implemented yet
     return ((int64_t)x) * F / y;
 }
 
 /* Divide fpa by integer */
 fpa fpa_div_by_int(fpa x, int i) {
     // not implemented yet
     return x / i;
 }