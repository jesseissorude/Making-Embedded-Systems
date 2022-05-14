# Exercise 7

### I.15: What is a reentrant function?

If an interrupt occurs the processor sees a flag, saves the current states of various registers, 
then handles the interrupt.  There could be instances where the interrupt changes the value of a 
variable that was being worked with just when the interrupt came.  If changing the value of a 
memory location, register, etc could wreck the outcome of the function the processor was in at 
the time of the interrupt, then the function is non-reentrant.

If the processor was in the middle of a reentrant function, there would be no issue.  A reentrant
function can be paused to handle interrupts because it either does not depend on global values that
could change, or specifically blocks sensitive parts of its algorithm from being interrupted.

### R.9: Given an integer variable a, write two code fragments. The first should set bit 3 of a. The second should clear bit 3 of a. In both cases, the other bits should be unmodified.

a |= 1U << 3;  // Sets the third bit

a &= ~(1U << 3);  // Clears the third bit