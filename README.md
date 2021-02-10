# Swamp

__In progress__.

Cooperative multitasking operating system for Cortex-M4 **STM32F4xx** controllers.
See *sample.c* to understand how to use the system and its modules.

Building samples:
```
make MODULES="sample kernel" all
```

Clean samples:
```
make MODULES="sample kernel" clean
```

Building your application:
```
make MODULES="app kernel" all
```
