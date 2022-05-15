

module DE1_SoC_Computer (
	////////////////////////////////////
	// FPGA Pins
	////////////////////////////////////

	// Clock pins
	CLOCK_50,
	CLOCK2_50,
	CLOCK3_50,
	CLOCK4_50,

	// ADC
	ADC_CS_N,
	ADC_DIN,
	ADC_DOUT,
	ADC_SCLK,

	// Audio
	AUD_ADCDAT,
	AUD_ADCLRCK,
	AUD_BCLK,
	AUD_DACDAT,
	AUD_DACLRCK,
	AUD_XCK,

	// SDRAM
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_LDQM,
	DRAM_RAS_N,
	DRAM_UDQM,
	DRAM_WE_N,

	// I2C Bus for Configuration of the Audio and Video-In Chips
	FPGA_I2C_SCLK,
	FPGA_I2C_SDAT,

	// 40-Pin Headers
	GPIO_0,
	GPIO_1,
	
	// Seven Segment Displays
	HEX0,
	HEX1,
	HEX2,
	HEX3,
	HEX4,
	HEX5,

	// IR
	IRDA_RXD,
	IRDA_TXD,

	// Pushbuttons
	KEY,

	// LEDs
	LEDR,

	// PS2 Ports
	PS2_CLK,
	PS2_DAT,
	
	PS2_CLK2,
	PS2_DAT2,

	// Slider Switches
	SW,

	// Video-In
	TD_CLK27,
	TD_DATA,
	TD_HS,
	TD_RESET_N,
	TD_VS,

	// VGA
	VGA_B,
	VGA_BLANK_N,
	VGA_CLK,
	VGA_G,
	VGA_HS,
	VGA_R,
	VGA_SYNC_N,
	VGA_VS,

	////////////////////////////////////
	// HPS Pins
	////////////////////////////////////
	
	// DDR3 SDRAM
	HPS_DDR3_ADDR,
	HPS_DDR3_BA,
	HPS_DDR3_CAS_N,
	HPS_DDR3_CKE,
	HPS_DDR3_CK_N,
	HPS_DDR3_CK_P,
	HPS_DDR3_CS_N,
	HPS_DDR3_DM,
	HPS_DDR3_DQ,
	HPS_DDR3_DQS_N,
	HPS_DDR3_DQS_P,
	HPS_DDR3_ODT,
	HPS_DDR3_RAS_N,
	HPS_DDR3_RESET_N,
	HPS_DDR3_RZQ,
	HPS_DDR3_WE_N,

	// Ethernet
	HPS_ENET_GTX_CLK,
	HPS_ENET_INT_N,
	HPS_ENET_MDC,
	HPS_ENET_MDIO,
	HPS_ENET_RX_CLK,
	HPS_ENET_RX_DATA,
	HPS_ENET_RX_DV,
	HPS_ENET_TX_DATA,
	HPS_ENET_TX_EN,

	// Flash
	HPS_FLASH_DATA,
	HPS_FLASH_DCLK,
	HPS_FLASH_NCSO,

	// Accelerometer
	HPS_GSENSOR_INT,
		
	// General Purpose I/O
	HPS_GPIO,
		
	// I2C
	HPS_I2C_CONTROL,
	HPS_I2C1_SCLK,
	HPS_I2C1_SDAT,
	HPS_I2C2_SCLK,
	HPS_I2C2_SDAT,

	// Pushbutton
	HPS_KEY,

	// LED
	HPS_LED,
		
	// SD Card
	HPS_SD_CLK,
	HPS_SD_CMD,
	HPS_SD_DATA,

	// SPI
	HPS_SPIM_CLK,
	HPS_SPIM_MISO,
	HPS_SPIM_MOSI,
	HPS_SPIM_SS,

	// UART
	HPS_UART_RX,
	HPS_UART_TX,

	// USB
	HPS_CONV_USB_N,
	HPS_USB_CLKOUT,
	HPS_USB_DATA,
	HPS_USB_DIR,
	HPS_USB_NXT,
	HPS_USB_STP
);

//=======================================================
//  PARAMETER declarations
//=======================================================


//=======================================================
//  PORT declarations
//=======================================================

////////////////////////////////////
// FPGA Pins
////////////////////////////////////

// Clock pins
input						CLOCK_50;
input						CLOCK2_50;
input						CLOCK3_50;
input						CLOCK4_50;

// ADC
inout						ADC_CS_N;
output					ADC_DIN;
input						ADC_DOUT;
output					ADC_SCLK;

// Audio
input						AUD_ADCDAT;
inout						AUD_ADCLRCK;
inout						AUD_BCLK;
output					AUD_DACDAT;
inout						AUD_DACLRCK;
output					AUD_XCK;

// SDRAM
output 		[12: 0]	DRAM_ADDR;
output		[ 1: 0]	DRAM_BA;
output					DRAM_CAS_N;
output					DRAM_CKE;
output					DRAM_CLK;
output					DRAM_CS_N;
inout			[15: 0]	DRAM_DQ;
output					DRAM_LDQM;
output					DRAM_RAS_N;
output					DRAM_UDQM;
output					DRAM_WE_N;

// I2C Bus for Configuration of the Audio and Video-In Chips
output					FPGA_I2C_SCLK;
inout						FPGA_I2C_SDAT;

// 40-pin headers
inout			[35: 0]	GPIO_0;
inout			[35: 0]	GPIO_1;

// Seven Segment Displays
output		[ 6: 0]	HEX0;
output		[ 6: 0]	HEX1;
output		[ 6: 0]	HEX2;
output		[ 6: 0]	HEX3;
output		[ 6: 0]	HEX4;
output		[ 6: 0]	HEX5;

// IR
input						IRDA_RXD;
output					IRDA_TXD;

// Pushbuttons
input			[ 3: 0]	KEY;

// LEDs
output		[ 9: 0]	LEDR;

// PS2 Ports
inout						PS2_CLK;
inout						PS2_DAT;

inout						PS2_CLK2;
inout						PS2_DAT2;

// Slider Switches
input			[ 9: 0]	SW;

// Video-In
input						TD_CLK27;
input			[ 7: 0]	TD_DATA;
input						TD_HS;
output					TD_RESET_N;
input						TD_VS;

// VGA
output		[ 7: 0]	VGA_B;
output					VGA_BLANK_N;
output					VGA_CLK;
output		[ 7: 0]	VGA_G;
output					VGA_HS;
output		[ 7: 0]	VGA_R;
output					VGA_SYNC_N;
output					VGA_VS;



////////////////////////////////////
// HPS Pins
////////////////////////////////////
	
// DDR3 SDRAM
output		[14: 0]	HPS_DDR3_ADDR;
output		[ 2: 0]  HPS_DDR3_BA;
output					HPS_DDR3_CAS_N;
output					HPS_DDR3_CKE;
output					HPS_DDR3_CK_N;
output					HPS_DDR3_CK_P;
output					HPS_DDR3_CS_N;
output		[ 3: 0]	HPS_DDR3_DM;
inout			[31: 0]	HPS_DDR3_DQ;
inout			[ 3: 0]	HPS_DDR3_DQS_N;
inout			[ 3: 0]	HPS_DDR3_DQS_P;
output					HPS_DDR3_ODT;
output					HPS_DDR3_RAS_N;
output					HPS_DDR3_RESET_N;
input						HPS_DDR3_RZQ;
output					HPS_DDR3_WE_N;

// Ethernet
output					HPS_ENET_GTX_CLK;
inout						HPS_ENET_INT_N;
output					HPS_ENET_MDC;
inout						HPS_ENET_MDIO;
input						HPS_ENET_RX_CLK;
input			[ 3: 0]	HPS_ENET_RX_DATA;
input						HPS_ENET_RX_DV;
output		[ 3: 0]	HPS_ENET_TX_DATA;
output					HPS_ENET_TX_EN;

// Flash
inout			[ 3: 0]	HPS_FLASH_DATA;
output					HPS_FLASH_DCLK;
output					HPS_FLASH_NCSO;

// Accelerometer
inout						HPS_GSENSOR_INT;

// General Purpose I/O
inout			[ 1: 0]	HPS_GPIO;

// I2C
inout						HPS_I2C_CONTROL;
inout						HPS_I2C1_SCLK;
inout						HPS_I2C1_SDAT;
inout						HPS_I2C2_SCLK;
inout						HPS_I2C2_SDAT;

// Pushbutton
inout						HPS_KEY;

// LED
inout						HPS_LED;

// SD Card
output					HPS_SD_CLK;
inout						HPS_SD_CMD;
inout			[ 3: 0]	HPS_SD_DATA;

// SPI
output					HPS_SPIM_CLK;
input						HPS_SPIM_MISO;
output					HPS_SPIM_MOSI;
inout						HPS_SPIM_SS;

// UART
input						HPS_UART_RX;
output					HPS_UART_TX;

// USB
inout						HPS_CONV_USB_N;
input						HPS_USB_CLKOUT;
inout			[ 7: 0]	HPS_USB_DATA;
input						HPS_USB_DIR;
input						HPS_USB_NXT;
output					HPS_USB_STP;

//=======================================================
//  REG/WIRE declarations
//=======================================================

wire			[15: 0]	hex3_hex0;
//wire			[15: 0]	hex5_hex4;

//assign HEX0 = ~hex3_hex0[ 6: 0]; // hex3_hex0[ 6: 0]; 
//assign HEX1 = ~hex3_hex0[14: 8];
//assign HEX2 = ~hex3_hex0[22:16];
//assign HEX3 = ~hex3_hex0[30:24];
assign HEX4 = 7'b1111111;
assign HEX5 = 7'b1111111;

HexDigit Digit0(HEX0, hex3_hex0[3:0]);
HexDigit Digit1(HEX1, hex3_hex0[7:4]);
HexDigit Digit2(HEX2, hex3_hex0[11:8]);
HexDigit Digit3(HEX3, hex3_hex0[15:12]);


//lj

localparam NUM = 10;


wire signed [31:0] pio_fx [NUM-1:0];
wire signed [31:0] pio_fy [NUM-1:0];  
wire signed [31:0] pio_i_x [NUM-1:0]; 
wire signed [31:0] pio_i_y [NUM-1:0]; 
wire signed [31:0] pio_j_x [NUM-1:0];
wire signed [31:0] pio_j_y [NUM-1:0];



wire signed [26:0]fx_lj[NUM-1:0];
wire signed [26:0]fy_lj[NUM-1:0];



//assign LEDR[5:0] = pio_fx[0][31:26];


//instantiate lj

//lj test(
//	.part_pos_i_x(pio_i_x),
//	.part_pos_j_x(pio_j_x),
//	.part_pos_i_y(pio_i_y),
//	.part_pos_j_y(pio_j_y),
//	.clk(clk_50),
//	.reset(),
//	.fx_out(fx_lj),
//	.fy_out(fy_lj),
//	.ack()
//);

//instantiation of the arbiter 
//arbiter #(.NUMITER(NUM)) m0(
//
//	.clk(pio_fx),
//	.pio_fx(pio_fx[NUM-1:0]),
//	.pio_fy(pio_fy[NUM-1:0]),  
//	.pio_i_x(pio_i_x[NUM-1:0]),
//	.pio_i_y(pio_i_y[NUM-1:0]), 
//	.pio_j_x(pio_j_x[NUM-1:0]),
//	.pio_j_y(pio_j_y[NUM-1:0])
//   
//);

	
	
//	generate
//		  genvar i;
//		  for (i=0; i<NUM; i = i + 1) begin: parallel_solver
//
//			// each solver needs to recieve a cr, ci to start iterating on and control signals to synchronize with the control unit
//			lj it(
//					 .clk(CLOCK_50), 
//					 .reset(reset),
//					 .part_pos_i_x(pio_i_x[i]),
//					 .part_pos_j_x(pio_j_x[i]), 
//					 .part_pos_i_y(pio_i_y[i]), 
//					 .part_pos_j_y(pio_j_y[i]),
//					 .fx_out(fx_lj[i]),
//					 .fy_out(fy_lj[i]),
//					 .ack()
//			);
//			
//			assign pio_fx[i]  = {{5{fx_lj[i][26]}},fx_lj[i]};
//			assign pio_fy[i]  = {{5{fy_lj[i][26]}},fy_lj[i]};
//			
//
//
//		  end
//
//	endgenerate


lj it0(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[0]),
		 .part_pos_j_x(pio_j_x[0]), 
		 .part_pos_i_y(pio_i_y[0]), 
		 .part_pos_j_y(pio_j_y[0]),
		 .fx_out(fx_lj[0]),
		 .fy_out(fy_lj[0]),
		 .ack()
);

assign pio_fx[0]  = {{5{fx_lj[0][26]}},fx_lj[0]};
assign pio_fy[0]  = {{5{fy_lj[0][26]}},fy_lj[0]};


lj it1(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[1]),
		 .part_pos_j_x(pio_j_x[1]), 
		 .part_pos_i_y(pio_i_y[1]), 
		 .part_pos_j_y(pio_j_y[1]),
		 .fx_out(fx_lj[1]),
		 .fy_out(fy_lj[1]),
		 .ack()
);

assign pio_fx[1]  = {{5{fx_lj[1][26]}},fx_lj[1]};
assign pio_fy[1]  = {{5{fy_lj[1][26]}},fy_lj[1]};

lj it2(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[2]),
		 .part_pos_j_x(pio_j_x[2]), 
		 .part_pos_i_y(pio_i_y[2]), 
		 .part_pos_j_y(pio_j_y[2]),
		 .fx_out(fx_lj[2]),
		 .fy_out(fy_lj[2]),
		 .ack()
);

assign pio_fx[2]  = {{5{fx_lj[2][26]}},fx_lj[2]};
assign pio_fy[2]  = {{5{fy_lj[2][26]}},fy_lj[2]};

lj it3(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[3]),
		 .part_pos_j_x(pio_j_x[3]), 
		 .part_pos_i_y(pio_i_y[3]), 
		 .part_pos_j_y(pio_j_y[3]),
		 .fx_out(fx_lj[3]),
		 .fy_out(fy_lj[3]),
		 .ack()
);

assign pio_fx[3]  = {{5{fx_lj[3][26]}},fx_lj[3]};
assign pio_fy[3]  = {{5{fy_lj[3][26]}},fy_lj[3]};

lj it4(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[4]),
		 .part_pos_j_x(pio_j_x[4]), 
		 .part_pos_i_y(pio_i_y[4]), 
		 .part_pos_j_y(pio_j_y[4]),
		 .fx_out(fx_lj[4]),
		 .fy_out(fy_lj[4]),
		 .ack()
);

assign pio_fx[4]  = {{5{fx_lj[4][26]}},fx_lj[4]};
assign pio_fy[4]  = {{5{fy_lj[4][26]}},fy_lj[4]};

lj it5(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[5]),
		 .part_pos_j_x(pio_j_x[5]), 
		 .part_pos_i_y(pio_i_y[5]), 
		 .part_pos_j_y(pio_j_y[5]),
		 .fx_out(fx_lj[5]),
		 .fy_out(fy_lj[5]),
		 .ack()
);

assign pio_fx[5]  = {{5{fx_lj[5][26]}},fx_lj[5]};
assign pio_fy[5]  = {{5{fy_lj[5][26]}},fy_lj[5]};

lj it6(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[6]),
		 .part_pos_j_x(pio_j_x[6]), 
		 .part_pos_i_y(pio_i_y[6]), 
		 .part_pos_j_y(pio_j_y[6]),
		 .fx_out(fx_lj[6]),
		 .fy_out(fy_lj[6]),
		 .ack()
);

assign pio_fx[6]  = {{5{fx_lj[6][26]}},fx_lj[6]};
assign pio_fy[6]  = {{5{fy_lj[6][26]}},fy_lj[6]};

lj it7(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[7]),
		 .part_pos_j_x(pio_j_x[7]), 
		 .part_pos_i_y(pio_i_y[7]), 
		 .part_pos_j_y(pio_j_y[7]),
		 .fx_out(fx_lj[7]),
		 .fy_out(fy_lj[7]),
		 .ack()
);

assign pio_fx[7]  = {{5{fx_lj[7][26]}},fx_lj[7]};
assign pio_fy[7]  = {{5{fy_lj[7][26]}},fy_lj[7]};

lj it8(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[8]),
		 .part_pos_j_x(pio_j_x[8]), 
		 .part_pos_i_y(pio_i_y[8]), 
		 .part_pos_j_y(pio_j_y[8]),
		 .fx_out(fx_lj[8]),
		 .fy_out(fy_lj[8]),
		 .ack()
);

assign pio_fx[8]  = {{5{fx_lj[8][26]}},fx_lj[8]};
assign pio_fy[8]  = {{5{fy_lj[8][26]}},fy_lj[8]};

lj it9(
		 .clk(CLOCK_50), 
		 .reset(reset),
		 .part_pos_i_x(pio_i_x[9]),
		 .part_pos_j_x(pio_j_x[9]), 
		 .part_pos_i_y(pio_i_y[9]), 
		 .part_pos_j_y(pio_j_y[9]),
		 .fx_out(fx_lj[9]),
		 .fy_out(fy_lj[9]),
		 .ack()
);

assign pio_fx[9]  = {{5{fx_lj[9][26]}},fx_lj[9]};
assign pio_fy[9]  = {{5{fy_lj[9][26]}},fy_lj[9]};


//=======================================================
//  Structural coding
//=======================================================

Computer_System The_System (
	////////////////////////////////////
	// FPGA Side
	////////////////////////////////////

	// Global signals
	.system_pll_ref_clk_clk					(CLOCK_50),
	.system_pll_ref_reset_reset			(1'b0),

	// AV Config
	.av_config_SCLK							(FPGA_I2C_SCLK),
	.av_config_SDAT							(FPGA_I2C_SDAT),

	// VGA Subsystem
	.vga_pll_ref_clk_clk 					(CLOCK2_50),
	.vga_pll_ref_reset_reset				(1'b0),
	.vga_CLK										(VGA_CLK),
	.vga_BLANK									(VGA_BLANK_N),
	.vga_SYNC									(VGA_SYNC_N),
	.vga_HS										(VGA_HS),
	.vga_VS										(VGA_VS),
	.vga_R										(VGA_R),
	.vga_G										(VGA_G),
	.vga_B										(VGA_B),
	
	// SDRAM
	.sdram_clk_clk								(DRAM_CLK),
   .sdram_addr									(DRAM_ADDR),
	.sdram_ba									(DRAM_BA),
	.sdram_cas_n								(DRAM_CAS_N),
	.sdram_cke									(DRAM_CKE),
	.sdram_cs_n									(DRAM_CS_N),
	.sdram_dq									(DRAM_DQ),
	.sdram_dqm									({DRAM_UDQM,DRAM_LDQM}),
	.sdram_ras_n								(DRAM_RAS_N),
	.sdram_we_n									(DRAM_WE_N),
	
	////////////////////////////////////
	// HPS Side
	////////////////////////////////////
	// DDR3 SDRAM
	.memory_mem_a			(HPS_DDR3_ADDR),
	.memory_mem_ba			(HPS_DDR3_BA),
	.memory_mem_ck			(HPS_DDR3_CK_P),
	.memory_mem_ck_n		(HPS_DDR3_CK_N),
	.memory_mem_cke		(HPS_DDR3_CKE),
	.memory_mem_cs_n		(HPS_DDR3_CS_N),
	.memory_mem_ras_n		(HPS_DDR3_RAS_N),
	.memory_mem_cas_n		(HPS_DDR3_CAS_N),
	.memory_mem_we_n		(HPS_DDR3_WE_N),
	.memory_mem_reset_n	(HPS_DDR3_RESET_N),
	.memory_mem_dq			(HPS_DDR3_DQ),
	.memory_mem_dqs		(HPS_DDR3_DQS_P),
	.memory_mem_dqs_n		(HPS_DDR3_DQS_N),
	.memory_mem_odt		(HPS_DDR3_ODT),
	.memory_mem_dm			(HPS_DDR3_DM),
	.memory_oct_rzqin		(HPS_DDR3_RZQ),
		  
	// Ethernet
	.hps_io_hps_io_gpio_inst_GPIO35	(HPS_ENET_INT_N),
	.hps_io_hps_io_emac1_inst_TX_CLK	(HPS_ENET_GTX_CLK),
	.hps_io_hps_io_emac1_inst_TXD0	(HPS_ENET_TX_DATA[0]),
	.hps_io_hps_io_emac1_inst_TXD1	(HPS_ENET_TX_DATA[1]),
	.hps_io_hps_io_emac1_inst_TXD2	(HPS_ENET_TX_DATA[2]),
	.hps_io_hps_io_emac1_inst_TXD3	(HPS_ENET_TX_DATA[3]),
	.hps_io_hps_io_emac1_inst_RXD0	(HPS_ENET_RX_DATA[0]),
	.hps_io_hps_io_emac1_inst_MDIO	(HPS_ENET_MDIO),
	.hps_io_hps_io_emac1_inst_MDC		(HPS_ENET_MDC),
	.hps_io_hps_io_emac1_inst_RX_CTL	(HPS_ENET_RX_DV),
	.hps_io_hps_io_emac1_inst_TX_CTL	(HPS_ENET_TX_EN),
	.hps_io_hps_io_emac1_inst_RX_CLK	(HPS_ENET_RX_CLK),
	.hps_io_hps_io_emac1_inst_RXD1	(HPS_ENET_RX_DATA[1]),
	.hps_io_hps_io_emac1_inst_RXD2	(HPS_ENET_RX_DATA[2]),
	.hps_io_hps_io_emac1_inst_RXD3	(HPS_ENET_RX_DATA[3]),

	// Flash
	.hps_io_hps_io_qspi_inst_IO0	(HPS_FLASH_DATA[0]),
	.hps_io_hps_io_qspi_inst_IO1	(HPS_FLASH_DATA[1]),
	.hps_io_hps_io_qspi_inst_IO2	(HPS_FLASH_DATA[2]),
	.hps_io_hps_io_qspi_inst_IO3	(HPS_FLASH_DATA[3]),
	.hps_io_hps_io_qspi_inst_SS0	(HPS_FLASH_NCSO),
	.hps_io_hps_io_qspi_inst_CLK	(HPS_FLASH_DCLK),

	// Accelerometer
	.hps_io_hps_io_gpio_inst_GPIO61	(HPS_GSENSOR_INT),

	//.adc_sclk                        (ADC_SCLK),
	//.adc_cs_n                        (ADC_CS_N),
	//.adc_dout                        (ADC_DOUT),
	//.adc_din                         (ADC_DIN),

	// General Purpose I/O
	.hps_io_hps_io_gpio_inst_GPIO40	(HPS_GPIO[0]),
	.hps_io_hps_io_gpio_inst_GPIO41	(HPS_GPIO[1]),

	// I2C
	.hps_io_hps_io_gpio_inst_GPIO48	(HPS_I2C_CONTROL),
	.hps_io_hps_io_i2c0_inst_SDA		(HPS_I2C1_SDAT),
	.hps_io_hps_io_i2c0_inst_SCL		(HPS_I2C1_SCLK),
	.hps_io_hps_io_i2c1_inst_SDA		(HPS_I2C2_SDAT),
	.hps_io_hps_io_i2c1_inst_SCL		(HPS_I2C2_SCLK),

	// Pushbutton
	.hps_io_hps_io_gpio_inst_GPIO54	(HPS_KEY),

	// LED
	.hps_io_hps_io_gpio_inst_GPIO53	(HPS_LED),

	// SD Card
	.hps_io_hps_io_sdio_inst_CMD	(HPS_SD_CMD),
	.hps_io_hps_io_sdio_inst_D0	(HPS_SD_DATA[0]),
	.hps_io_hps_io_sdio_inst_D1	(HPS_SD_DATA[1]),
	.hps_io_hps_io_sdio_inst_CLK	(HPS_SD_CLK),
	.hps_io_hps_io_sdio_inst_D2	(HPS_SD_DATA[2]),
	.hps_io_hps_io_sdio_inst_D3	(HPS_SD_DATA[3]),

	// SPI
	.hps_io_hps_io_spim1_inst_CLK		(HPS_SPIM_CLK),
	.hps_io_hps_io_spim1_inst_MOSI	(HPS_SPIM_MOSI),
	.hps_io_hps_io_spim1_inst_MISO	(HPS_SPIM_MISO),
	.hps_io_hps_io_spim1_inst_SS0		(HPS_SPIM_SS),

	// UART
	.hps_io_hps_io_uart0_inst_RX	(HPS_UART_RX),
	.hps_io_hps_io_uart0_inst_TX	(HPS_UART_TX),

	// USB
	.hps_io_hps_io_gpio_inst_GPIO09	(HPS_CONV_USB_N),
	.hps_io_hps_io_usb1_inst_D0		(HPS_USB_DATA[0]),
	.hps_io_hps_io_usb1_inst_D1		(HPS_USB_DATA[1]),
	.hps_io_hps_io_usb1_inst_D2		(HPS_USB_DATA[2]),
	.hps_io_hps_io_usb1_inst_D3		(HPS_USB_DATA[3]),
	.hps_io_hps_io_usb1_inst_D4		(HPS_USB_DATA[4]),
	.hps_io_hps_io_usb1_inst_D5		(HPS_USB_DATA[5]),
	.hps_io_hps_io_usb1_inst_D6		(HPS_USB_DATA[6]),
	.hps_io_hps_io_usb1_inst_D7		(HPS_USB_DATA[7]),
	.hps_io_hps_io_usb1_inst_CLK		(HPS_USB_CLKOUT),
	.hps_io_hps_io_usb1_inst_STP		(HPS_USB_STP),
	.hps_io_hps_io_usb1_inst_DIR		(HPS_USB_DIR),
	.hps_io_hps_io_usb1_inst_NXT		(HPS_USB_NXT),
	
	//lj
	
	.pio_fx_external_connection_export(pio_fx[0]),
	.pio_fy_external_connection_export(pio_fy[0]),
	.pio_i_x_external_connection_export(pio_i_x[0]),
	.pio_i_y_external_connection_export(pio_i_y[0]),
	.pio_j_x_external_connection_export(pio_j_x[0]),
	.pio_j_y_external_connection_export(pio_j_y[0]),
	.pio_fx_1_external_connection_export(pio_fx[1]),
	.pio_fy_1_external_connection_export(pio_fy[1]),
	.pio_i_x_1_external_connection_export(pio_i_x[1]),
	.pio_i_y_1_external_connection_export(pio_i_y[1]),
	.pio_j_x_1_external_connection_export(pio_j_x[1]),
	.pio_j_y_1_external_connection_export(pio_j_y[1]),
	.pio_fx_2_external_connection_export(pio_fx[2]),
	.pio_fy_2_external_connection_export(pio_fy[2]),
	.pio_i_x_2_external_connection_export(pio_i_x[2]),
	.pio_i_y_2_external_connection_export(pio_i_y[2]),
	.pio_j_x_2_external_connection_export(pio_j_x[2]),
	.pio_j_y_2_external_connection_export(pio_j_y[2]),
	.pio_fx_3_external_connection_export(pio_fx[3]),
	.pio_fy_3_external_connection_export(pio_fy[3]),
	.pio_i_x_3_external_connection_export(pio_i_x[3]),
	.pio_i_y_3_external_connection_export(pio_i_y[3]),
	.pio_j_x_3_external_connection_export(pio_j_x[3]),
	.pio_j_y_3_external_connection_export(pio_j_y[3]),
	.pio_fx_4_external_connection_export(pio_fx[4]),
	.pio_fy_4_external_connection_export(pio_fy[4]),
	.pio_i_x_4_external_connection_export(pio_i_x[4]),
	.pio_i_y_4_external_connection_export(pio_i_y[4]),
	.pio_j_x_4_external_connection_export(pio_j_x[4]),
	.pio_j_y_4_external_connection_export(pio_j_y[4]),
	.pio_fx_5_external_connection_export(pio_fx[5]),
	.pio_fy_5_external_connection_export(pio_fy[5]),
	.pio_i_x_5_external_connection_export(pio_i_x[5]),
	.pio_i_y_5_external_connection_export(pio_i_y[5]),
	.pio_j_x_5_external_connection_export(pio_j_x[5]),
	.pio_j_y_5_external_connection_export(pio_j_y[5]),
	.pio_fx_6_external_connection_export(pio_fx[6]),
	.pio_fy_6_external_connection_export(pio_fy[6]),
	.pio_i_x_6_external_connection_export(pio_i_x[6]),
	.pio_i_y_6_external_connection_export(pio_i_y[6]),
	.pio_j_x_6_external_connection_export(pio_j_x[6]),
	.pio_j_y_6_external_connection_export(pio_j_y[6]),
	.pio_fx_7_external_connection_export(pio_fx[7]),
	.pio_fy_7_external_connection_export(pio_fy[7]),
	.pio_i_x_7_external_connection_export(pio_i_x[7]),
	.pio_i_y_7_external_connection_export(pio_i_y[7]),
	.pio_j_x_7_external_connection_export(pio_j_x[7]),
	.pio_j_y_7_external_connection_export(pio_j_y[7]),
	.pio_fx_8_external_connection_export(pio_fx[8]),
	.pio_fy_8_external_connection_export(pio_fy[8]),
	.pio_i_x_8_external_connection_export(pio_i_x[8]),
	.pio_i_y_8_external_connection_export(pio_i_y[8]),
	.pio_j_x_8_external_connection_export(pio_j_x[8]),
	.pio_j_y_8_external_connection_export(pio_j_y[8]),
	.pio_fx_9_external_connection_export(pio_fx[9]),
	.pio_fy_9_external_connection_export(pio_fy[9]),
	.pio_i_x_9_external_connection_export(pio_i_x[9]),
	.pio_i_y_9_external_connection_export(pio_i_y[9]),
	.pio_j_x_9_external_connection_export(pio_j_x[9]),
	.pio_j_y_9_external_connection_export(pio_j_y[9])

);


endmodule

//
//module arbiter(
//
//
//	input clk, 
//	input rst,
//	output reg signed [31:0] pio_fx [NUMITER-1:0],
//	output reg signed [31:0] pio_fy [NUMITER-1:0],
//	input signed [31:0] pio_i_x [NUMITER-1:0], 
//	input signed [31:0] pio_i_y [NUMITER-1:0], 
//	input signed [31:0] pio_j_x [NUMITER-1:0],
//	input signed [31:0] pio_j_y [NUMITER-1:0]
//);
//
//
//
//endmodule


module lj(
    input signed [26:0] part_pos_i_x,
    input signed [26:0] part_pos_j_x,
    input signed [26:0] part_pos_i_y,
    input signed [26:0] part_pos_j_y,
	 input clk, 
	 input reset,

    output reg signed [26:0] fx_out,
    output reg signed [26:0] fy_out,
    output reg ack
);

	reg signed [26:0] forceCutoff = 15 << 17; 
	reg signed [26:0] forceCutoff2 = 255 << 17; 
	
	localparam elasticCoeff = 6;
	reg signed [26:0] elasticCutoff = 25<<17;

	wire signed [26:0] dx,dx2;
	assign dx = part_pos_i_x - part_pos_j_x;
	signed_mult m_dx2(dx2,dx,dx);

	wire signed [26:0] dy,dy2; 
	assign dy = part_pos_i_y - part_pos_j_y;
	signed_mult m_dy2(dy2,dy,dy);

	wire signed [26:0] r2,rinv2_int, rinv2;
	assign r2=dx2+dy2;
	sync_rom_2_reduced rom(r2+((27'b1)<< 17), rinv2_int);
	assign rinv2 = rinv2_int<<6;

	reg signed [26:0] attract;
	wire signed[26:0] attract_mult;
	wire signed [26:0] rinv4;
	signed_mult m_a1(rinv4,rinv2,rinv2);
	signed_mult m_a2(attract_mult,rinv2,rinv4);

	reg signed [26:0] repel;
	wire signed [26:0] repel_mult;

	signed_mult m_r(repel_mult,attract,attract);

	wire signed [26:0] fOverR, fOverR_intermediate;

	assign fOverR_intermediate = (((repel<<1) - attract)<<5);
	signed_mult m_fOr(fOverR,fOverR_intermediate,rinv2);

	wire signed [26:0] fx,fy;

	signed_mult m_fx(fx,fOverR,dx);
	signed_mult m_fy(fy,fOverR,dy);
	
	
	wire signed [26:0] fx_elas,fy_elas;


	always@(*) begin
	//
	//		attract = attract_mult;
	//		repel = repel_mult;
		 if(attract_mult>(1<<17)) begin
			  attract = 1<<17;
		 end
		 else begin
			  attract = attract_mult;
		 end
		 if(repel_mult>(3<<16)) begin
			  repel = 3<<16;
		 end
		 else begin
			  repel = repel_mult;
		 end
		 

		 if((dx < forceCutoff && dx > -forceCutoff) && (dy < forceCutoff && dy > -forceCutoff)) begin
			  if(r2<forceCutoff2) begin
			  
			  		 if(r2<elasticCutoff) begin
					  fx_out = fx + dx<<elasticCoeff;
					  fy_out = fy + dy<<elasticCoeff;
					 end
					 else begin
					  fx_out = fx;
					  fy_out = fy;
					 end

					  ack=1;
			  end
			  else begin
				fx_out = 0;
				fy_out = 0;
				ack=0;
			 end

		 end
		 else begin
			fx_out = 0;
			fy_out = 0;
			ack=0;
		 end
		 


	end


endmodule



module signed_mult (out, a, b);
	output 	signed  [26:0]	out;
	input 	signed	[26:0] 	a;
	input 	signed	[26:0] 	b;
	wire 	signed	[53:0]	mult_out;
	assign mult_out = a * b;
	assign out = {mult_out[53], mult_out[42:17]};
endmodule
