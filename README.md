# Blank project example


## How to create components

All components are placed in components directory in its own folder. In the same folder, CMakeLists.txt must be created. The example CMakeLists.txt:
```
idf_component_register(SRCS "your_component.c"
                    INCLUDE_DIRS "."
                    REQUIRES Modem)
```
REQUIRES is only necessary when you have a dependacy that your component depends on. Normally this would be none so use:

```
idf_component_register(SRCS "your_component.c"
                    INCLUDE_DIRS ".")
```

"# esp32_rtos_test" 
