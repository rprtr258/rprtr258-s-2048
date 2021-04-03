plugins {
    `cpp-application`
}

application {
    targetMachines.add(machines.windows.x86_64)
}

val sfml_dir: String = "../SFML-2.5.1"

tasks.withType(CppCompile::class.java).configureEach {
    macros.put("SFML_STATIC", null)
    compilerArgs.add("-Wall")
    includes.from(file("$sfml_dir/include"))
}

tasks.withType(LinkExecutable::class.java).configureEach {
    linkerArgs.addAll(listOf(
        "-L", "$sfml_dir/lib",
        "-lsfml-graphics-s",
        "-lsfml-window-s",
        "-lsfml-system-s",
        "-lopengl32",
        "-lwinmm",
        "-lgdi32"
    ))
}

tasks.register<Copy>("assemble-release") {
    dependsOn("build")

    from("resources")
    into("$buildDir/exe/main/debug")
}

tasks.register<Zip>("release") {
    dependsOn("assemble-release")

    destinationDirectory.set(file("$buildDir/dist"))
    from("$buildDir/exe/main/debug/")
    archiveFileName.set("0.0.2.zip")
}
