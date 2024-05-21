package com.example.myapplication;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

/**
 * The PizzaOptionsAdapter class defines the adapter used to display what pizzas can be ordered.
 */
public class PizzaOptionsAdapter extends RecyclerView.Adapter<PizzaOptionsAdapter.ItemsHolder> {

    private Context context;
    private ArrayList<PizzaOption> pizzaOptions;

    /**
     * Initializes this adapter by using the context the adapter is used in and the list of options.
     * @param context the context the adapter is used in.
     * @param pizzaOptions the list of options, as represented by PizzaOption instances.
     */
    public PizzaOptionsAdapter(Context context, ArrayList<PizzaOption> pizzaOptions){
        this.context = context;
        this.pizzaOptions = pizzaOptions;
    }

    /**
     * Creates the ItemsHolder for the options that can be selected by the user.
     * @param parent the View that the ItemsHolder will be displayed in.
     * @param viewType the type of View used.
     * @return the ItemsHolder created.
     */
    @NonNull
    @Override
    public ItemsHolder onCreateViewHolder(@NonNull ViewGroup parent,
                                                              int viewType) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.pizza_style_row, parent, false);
        return new ItemsHolder(view);
    }

    /**
     * Binds the ItemsHolder to each option that can be selected by the user.
     * @param holder the ItemsHolder to be used.
     * @param position the position of the option being bound.
     */
    @Override
    public void onBindViewHolder(@NonNull ItemsHolder holder, int position) {
        holder.pizzaStyle.setText(pizzaOptions.get(position).getPizzaStyle());
        holder.pizzaFlavor.setText(pizzaOptions.get(position).getPizzaFlavor());
        holder.pizzaCrust.setText(pizzaOptions.get(position).getPizzaCrust());
        holder.pizzaImageView.setImageResource(pizzaOptions.get(position).getPizzaImage());
        holder.pizzaOption = pizzaOptions.get(position);
    }

    /**
     * Returns the number of options to be bound to the ViewHolder.
     * @return the number of options to be bound to the ViewHolder.
     */
    @Override
    public int getItemCount() {
        return pizzaOptions.size();
    }

    /**
     * The ItemsHolder class defines a ViewHolder to display information about the pizza option.
     * Three TextView instances are used to display the style, flavor, and crust of the pizza
     * option.
     * A Button instance is used to allow the user to customize the pizza option.
     * An ImageView instance is used to display an image of the pizza option.
     * A ConstraintLayout instance is used to define the constraint layout of the ViewHolder.
     * An instance of the PizzaOption being displayed is kept in order to pass information about the
     * option when it is customized.
     */
    public static class ItemsHolder extends RecyclerView.ViewHolder {

        private TextView pizzaStyle, pizzaFlavor, pizzaCrust;
        private Button selectPizzaButton;
        private ImageView pizzaImageView;
        private ConstraintLayout parentLayout;

        private PizzaOption pizzaOption;

        /**
         * Creates an ItemsHolder by referring to the layout used to display a pizza option.
         * The layout is defined in pizza_style_row.xml
         * @param itemView the View to use the ItemHolder in.
         */
        public ItemsHolder(@NonNull View itemView) {
            super(itemView);
            pizzaStyle = itemView.findViewById(R.id.styleTextView);
            pizzaFlavor = itemView.findViewById(R.id.flavorTextView);
            pizzaCrust = itemView.findViewById(R.id.pizzaCrust);
            pizzaImageView = itemView.findViewById(R.id.storeOrdersButton);
            selectPizzaButton = itemView.findViewById(R.id.selectPizzaButton);
            parentLayout = itemView.findViewById(R.id.parentLayout);
            initializeSelectPizzaButton();
        }

        /**
         * Sets an onClickListener for the Button used to let the user customize the PizzaOption.
         * The instance of PizzaOption is appended to the intent before the PizzaOptionsActivity is
         * started.
         */
        private void initializeSelectPizzaButton(){
            selectPizzaButton.setOnClickListener(v -> {
                Intent intent = new Intent(itemView.getContext(), PizzaOptionsActivity.class);
                intent.putExtra("PIZZA_OPTION", pizzaOption);
                itemView.getContext().startActivity(intent);
            });


        }



    }
}
