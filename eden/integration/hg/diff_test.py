
        repo.write_file("rootfile.txt", "")
        repo.write_file("dir1/a.txt", "original contents\n")
        repo.commit("Initial commit.")
        self.write_file("dir1/a.txt", "new line\noriginal contents\n")
        diff_output = self.hg("diff")
            "diff --git a/dir1/a.txt b/dir1/a.txt",
            "--- a/dir1/a.txt",
            "+++ b/dir1/a.txt",
            "@@ -1,1 +1,2 @@",
            "+new line",
            " original contents",
        self.write_file("dir1/b.txt", "new file\n1234\n5678\n")
        self.hg("add", "dir1/b.txt")
        diff_output = self.hg("diff")
            "diff --git a/dir1/b.txt b/dir1/b.txt",
            "new file mode 100644",
            "--- /dev/null",
            "+++ b/dir1/b.txt",
            "@@ -0,0 +1,3 @@",
            "+new file",
            "+1234",
            "+5678",