package config

import chisel3._

import math._

object Configs {
    val ADDR_WIDTH = 32
    val ADDR_BYTE_WIDTH = ADDR_WIDTH / 8
    val DATA_WIDTH = 32
    val DATA_WIDTH_H = DATA_WIDTH / 2
    val DATA_WIDTH_B = 8
    val START_ADDR = BigInt("80000004", 16)
    val INST_WIDTH = 32 // 指令位宽
    val INST_BYTE_WIDTH = INST_WIDTH / 8 // 指令位宽按字节算
    val INST_BYTE_WIDTH_LOG = ceil(log(INST_BYTE_WIDTH) / log(2)).toInt // 指令地址对齐的偏移量
    val MEM_INST_SIZE = 1024 // 指令内存大小
}