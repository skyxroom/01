open module nd4j.minimal.preset {
    requires nd4j.presets.common;
    requires nd4j.cpu.api;
    requires org.bytedeco.javacpp;
    exports org.nd4j.presets.cpu;
}
