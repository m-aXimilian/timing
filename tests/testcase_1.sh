echo "[INFO] remove db"
rm ../database/work_times_MK.db

echo "[INFO] building"
make

echo "[INFO] login"
./timing login

echo "[INFO] query db"
sqlite3 ../database/work_times_MK.db "select * from times_2021"

echo "[INFO] logout"
./timing logout

echo "[INFO] query db"
sqlite3 ../database/work_times_MK.db "select * from times_2021"


