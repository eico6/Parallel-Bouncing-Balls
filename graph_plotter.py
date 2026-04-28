import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("sim_par.csv")

df.set_index(df.columns[1], inplace=True)
# df.set_index("Category", inplace=True)

# Choose only specific segments
selected_columns = ["Clear time","Add to grid time","Collision time"]
df_selected = df[selected_columns]

df_selected.plot(
    kind="bar",
    stacked=True
)

plt.xlabel("Threads")
plt.ylabel("Time")
plt.title("Average times per frame (Parallel 10000 balls)")

plt.tight_layout()
plt.show()