echo "[INFO] logging out..."
./timing logout
echo "[INFO] query db"
sqlite3 ../database/work_times_MK.db "select * from times_2021"