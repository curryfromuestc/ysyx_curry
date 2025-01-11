package build_
import _root_.{build_ => $file}
import build_.{package_ => build}
import _root_.mill.runner.MillBuildRootModule
@_root_.scala.annotation.nowarn
object MillMiscInfo extends mill.main.RootModule.Info(
  Vector("/home/curry/code/ysyx_curry/npc/out/mill-launcher/0.12.5.jar"),
  "/home/curry/code/ysyx_curry/npc",
  "/home/curry/code/ysyx_curry/npc/out",
  "/home/curry/code/ysyx_curry/npc"
)
import MillMiscInfo._

object package_ extends package_{
  
  override lazy val millDiscover: _root_.mill.define.Discover = _root_.mill.define.Discover[this.type]

}
abstract class package_ extends _root_.mill.main.RootModule()  {
//MILL_ORIGINAL_FILE_PATH=/home/curry/code/ysyx_curry/npc/build.sc
//MILL_USER_CODE_START_MARKER
import mill._
import mill.define.Sources
import mill.modules.Util
import mill.scalalib.scalafmt.ScalafmtModule
import mill.scalalib.TestModule.ScalaTest
import mill.scalalib._
// support BSP
import mill.bsp._

object playground extends ScalaModule with ScalafmtModule { m =>
  override def scalaVersion = "2.13.15"

  override def scalacOptions = Seq(
    "-language:reflectiveCalls",
    "-deprecation",
    "-feature",
    "-Xcheckinit"
  )

  override def ivyDeps             = Agg(ivy"org.chipsalliance::chisel:6.6.0")
  override def scalacPluginIvyDeps = Agg(ivy"org.chipsalliance:::chisel-plugin:6.6.0")

  object test extends ScalaTests with TestModule.ScalaTest with ScalafmtModule {
    override def ivyDeps = m.ivyDeps() ++ Agg(
      ivy"org.scalatest::scalatest::3.2.19",
      // for formal flow in future
      ivy"edu.berkeley.cs::chiseltest:6.0.0"
    )
  }

  def repositoriesTask = T.task {
    Seq(
      coursier.MavenRepository("https://repo.scala-sbt.org/scalasbt/maven-releases"),
      coursier.MavenRepository("https://oss.sonatype.org/content/repositories/releases"),
      coursier.MavenRepository("https://oss.sonatype.org/content/repositories/snapshots")
    ) ++ super.repositoriesTask()
  }
}

}