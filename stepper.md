## A very silent stepper motor driver, TMC

[TMC 2209 - V1.2](https://github.com/bigtreetech/BIGTREETECH-TMC2209-V1.2/blob/master/manual/TMC2209-V1.2-manual.pdf)

I bought it from [Amazon](https://www.amazon.com/gp/product/B08SMDY3SQ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1).

Its [datasheet](https://github.com/bigtreetech/BIGTREETECH-TMC2209-V1.2/blob/master/manual/TMC2209-V1.2-manual.pdf).


### StealthChop & SpreadCycle

---

StealthChop is a quiet mode of operation for stepper motors at standstill and at low velocities. It is based on a voltage mode PWM. 

While stealthChop is a voltage mode PWM controlled chopper, spreadCycle is a cycle-by-cycle current control. It can react extremely fast to changes in motor velocity or motor load. spreadCycle will give better performance in medium to high velocity range for motors and applications which tend to resonance.