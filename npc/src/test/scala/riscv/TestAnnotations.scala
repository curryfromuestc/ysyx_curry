package riscv

import chiseltest.{VerilatorBackendAnnotation, WriteVcdAnnotation}
import firrtl2.AnnotationSeq

import java.nio.file.{Files, Paths}

/**
* 用于启用Verilator后端的注解
*/
object VerilatorEnabler {
  val annos: AnnotationSeq = if (sys.env.contains("Path")) {
    // Windows系统
    if (sys.env.getOrElse("Path", "").split(";").exists(path => {
      Files.exists(Paths.get(path, "verilator")) // 判断verilator是否存在
    })) {
      Seq(VerilatorBackendAnnotation).asInstanceOf[AnnotationSeq] // 启用Verilator后端
    } else{
      Seq() // 不启用Verilator后端
    }
  } else {
    // Linux系统
    if (sys.env.getOrElse("PATH", "").split(":").exists(path => {
      Files.exists(Paths.get(path, "verilator")) // 判断verilator是否存在
    })) {
      Seq(VerilatorBackendAnnotation).asInstanceOf[AnnotationSeq] // 启用Verilator后端
    } else {
      Seq() // 不启用Verilator后端
    }
  }
} // 这个写法的问题是 VerilatorBackendAnnotation 类型和 firrtl.AnnotationSeq 类型不一致， 无法通过编译
// 需要将 VerilatorBackendAnnotation 类型转换为 firrtl.AnnotationSeq 类型
// 可以使用 Seq(VerilatorBackendAnnotation).asInstanceOf[AnnotationSeq] 来实现类型转换

/**
* 用于启用VCD波形输出的注解
*/
object WriteVcdEnabler {
  val annos: AnnotationSeq = if (sys.env.contains("WRITE_VCD")) {
    // 启用VCD波形输出
    Seq(WriteVcdAnnotation).asInstanceOf[AnnotationSeq]
  } else {
    // 不启用VCD波形输出
    Seq()
  }
}

object TestAnnotations {
  // ++ 运算符用于连接两个AnnotationSeq
  val annos = VerilatorEnabler.annos ++ WriteVcdEnabler.annos
}