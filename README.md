#State logger:
- should hava a logic output containing the state
- should trigger a fixed time pulse (that will control communication device's startup)

Second point can be achieved with a 555 timer (ideally in retriggerable mode)

## First schematic attempt. Not retriggerable -> 555's reset to trigger ? Simulation doesn't work...

http://www.falstad.com/circuit/circuitjs.html?cct=$+1+0.000005+16.817414165184545+66+15+50%0Aw+96+160+128+160+0%0Aw+96+400+208+400+0%0A153+208+144+272+144+0+2+0+5%0Aw+208+160+208+128+0%0Aw+320+144+384+144+0%0A153+384+144+448+144+0+2+5+5%0Aw+384+128+384+144+0%0Aw+384+144+384+160+0%0Aw+448+144+480+144+0%0Ac+320+144+320+272+0+0.0000049999999999999996+0.000007984033161996305%0Ar+320+272+320+400+0+1000%0Ac+480+144+480+272+0+0.0000049999999999999996+4.999992007978827%0Ar+480+272+480+400+0+1000%0Aw+480+400+320+400+0%0Aw+320+400+208+400+0%0Aw+272+144+320+144+0%0Aw+320+272+448+272+0%0Aw+448+272+448+304+0%0Aw+448+304+528+304+0%0Aw+480+272+528+272+0%0A153+528+288+592+288+0+2+5+5%0Av+96+400+96+320+0+0+40+5+0+0+0.5%0Aw+96+224+96+160+0%0A165+752+240+800+240+2+0%0Aw+96+160+96+96+0%0Aw+816+96+816+208+0%0Aw+816+96+704+96+0%0Ar+704+96+704+176+0+1000%0Aw+704+176+704+272+0%0Aw+704+272+704+368+0%0Aw+704+368+704+400+0%0Ac+704+400+480+400+0+0.00009999999999999999+0.04950495470322665%0Aw+704+272+752+272+0%0Aw+752+368+704+368+0%0Aw+752+336+656+336+0%0Ac+816+400+816+432+0+1.0000000000000001e-7+3.333333333333236%0Aw+480+432+480+400+0%0Aw+96+96+704+96+0%0As+128+160+208+160+0+0+false%0Aw+96+320+96+224+0%0AM+880+304+912+304+0+2.5%0Aw+480+432+656+432+0%0Aw+656+432+816+432+0%0Aw+656+304+656+336+0%0Aw+880+272+880+96+0%0Aw+880+96+816+96+0%0Aw+656+304+656+288+0%0Aw+656+288+592+288+0%0Ao+40+64+0+4098+5+0.1+0+1%0A
