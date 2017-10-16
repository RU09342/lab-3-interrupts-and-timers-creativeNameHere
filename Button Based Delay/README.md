# Button Based Delay

This works by initially starting smclk/8 in up mode, with CCR0 = 6250. This leads to a signal of 20Hz. The button is held, and the press time is recorded. At some point afterwards, the button is released. Each time it overflows, a counter is incremented. On release, the counter is multiplied by the current CCR0 value, added to the current time, then the press time is subtracted. This yields how many cycles it's held for, and CCR0 is set to that.

As a result of CCR0 being 4 hex bits long, and the counter incrementing so often, it caps out around 0.5 seconds of being held. 
