deps_config := \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ppc32/bsp/qemu/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/bcm2835/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/integrator/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/kirkwood/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/exynos/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/sparc/bsp/leon3/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/pxa/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/sa1100/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/omap/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/ppc32/bsp/mpc52xx/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/tegra/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/s3c/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/imx/Kconfig \
	/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/kern/arm/bsp/realview/Kconfig \
	Kconfig

config/auto.conf: \
	$(deps_config)

ifneq "$(INCLUDE_SPARC)" ""
config/auto.conf: FORCE
endif
ifneq "$(INCLUDE_PPC32)" ""
config/auto.conf: FORCE
endif
ifneq "$(KERNELVERSION)" "SVN"
config/auto.conf: FORCE
endif

$(deps_config): ;
