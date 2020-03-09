float left_speed = 1;
float right_speed = 0.5;

/*
  - sit
  - blocking function
   ---------------------------------------------------------------------------*/
void sit(void)
{
    move_speed = stand_seat_speed;
    for (uint8_t leg = 0; leg < 4; leg++)
    {
        set_site(leg, KEEP, KEEP, z_boot);
    }
    wait_all_reach();
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void stand(void)
{
    move_speed = stand_seat_speed;
    for (uint8_t leg = 0; leg < 4; leg++)
    {
        set_site(leg, KEEP, KEEP, z_default);
    }
    wait_all_reach();
}

void turn_left(unsigned int step)
{
    move_speed = spot_turn_speed;
    while (step-- > 0)
    {
        if (site_now[3][1] == y_start)
        {
            //leg 3&1 move
            set_site(3, x_default + x_offset, y_start, z_up);
            wait_all_reach();

            set_site(0, turn_x1 - x_offset, turn_y1, z_default);
            set_site(1, turn_x0 - x_offset, turn_y0, z_default);
            set_site(2, turn_x1 + x_offset, turn_y1, z_default);
            set_site(3, turn_x0 + x_offset, turn_y0, z_up);
            wait_all_reach();

            set_site(3, turn_x0 + x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(0, turn_x1 + x_offset, turn_y1, z_default);
            set_site(1, turn_x0 + x_offset, turn_y0, z_default);
            set_site(2, turn_x1 - x_offset, turn_y1, z_default);
            set_site(3, turn_x0 - x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(1, turn_x0 + x_offset, turn_y0, z_up);
            wait_all_reach();

            set_site(0, x_default + x_offset, y_start, z_default);
            set_site(1, x_default + x_offset, y_start, z_up);
            set_site(2, x_default - x_offset, y_start + y_step, z_default);
            set_site(3, x_default - x_offset, y_start + y_step, z_default);
            wait_all_reach();

            set_site(1, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
        else
        {
            //leg 0&2 move
            set_site(0, x_default + x_offset, y_start, z_up);
            wait_all_reach();

            set_site(0, turn_x0 + x_offset, turn_y0, z_up);
            set_site(1, turn_x1 + x_offset, turn_y1, z_default);
            set_site(2, turn_x0 - x_offset, turn_y0, z_default);
            set_site(3, turn_x1 - x_offset, turn_y1, z_default);
            wait_all_reach();

            set_site(0, turn_x0 + x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(0, turn_x0 - x_offset, turn_y0, z_default);
            set_site(1, turn_x1 - x_offset, turn_y1, z_default);
            set_site(2, turn_x0 + x_offset, turn_y0, z_default);
            set_site(3, turn_x1 + x_offset, turn_y1, z_default);
            wait_all_reach();

            set_site(2, turn_x0 + x_offset, turn_y0, z_up);
            wait_all_reach();

            set_site(0, x_default - x_offset, y_start + y_step, z_default);
            set_site(1, x_default - x_offset, y_start + y_step, z_default);
            set_site(2, x_default + x_offset, y_start, z_up);
            set_site(3, x_default + x_offset, y_start, z_default);
            wait_all_reach();

            set_site(2, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
    }
}

/*
  - spot turn to right
  - blocking function
  - parameter step steps wanted to turn
   ---------------------------------------------------------------------------*/
void turn_right(unsigned int step)
{
    move_speed = spot_turn_speed;
    while (step-- > 0)
    {
        if (site_now[2][1] == y_start)
        {
            //leg 2&0 move
            set_site(2, x_default + x_offset, y_start, z_up);
            wait_all_reach();

            set_site(0, turn_x0 - x_offset, turn_y0, z_default);
            set_site(1, turn_x1 - x_offset, turn_y1, z_default);
            set_site(2, turn_x0 + x_offset, turn_y0, z_up);
            set_site(3, turn_x1 + x_offset, turn_y1, z_default);
            wait_all_reach();

            set_site(2, turn_x0 + x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(0, turn_x0 + x_offset, turn_y0, z_default);
            set_site(1, turn_x1 + x_offset, turn_y1, z_default);
            set_site(2, turn_x0 - x_offset, turn_y0, z_default);
            set_site(3, turn_x1 - x_offset, turn_y1, z_default);
            wait_all_reach();

            set_site(0, turn_x0 + x_offset, turn_y0, z_up);
            wait_all_reach();

            set_site(0, x_default + x_offset, y_start, z_up);
            set_site(1, x_default + x_offset, y_start, z_default);
            set_site(2, x_default - x_offset, y_start + y_step, z_default);
            set_site(3, x_default - x_offset, y_start + y_step, z_default);
            wait_all_reach();

            set_site(0, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
        else
        {
            //leg 1&3 move
            set_site(1, x_default + x_offset, y_start, z_up);
            wait_all_reach();

            set_site(0, turn_x1 + x_offset, turn_y1, z_default);
            set_site(1, turn_x0 + x_offset, turn_y0, z_up);
            set_site(2, turn_x1 - x_offset, turn_y1, z_default);
            set_site(3, turn_x0 - x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(1, turn_x0 + x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(0, turn_x1 - x_offset, turn_y1, z_default);
            set_site(1, turn_x0 - x_offset, turn_y0, z_default);
            set_site(2, turn_x1 + x_offset, turn_y1, z_default);
            set_site(3, turn_x0 + x_offset, turn_y0, z_default);
            wait_all_reach();

            set_site(3, turn_x0 + x_offset, turn_y0, z_up);
            wait_all_reach();

            set_site(0, x_default - x_offset, y_start + y_step, z_default);
            set_site(1, x_default - x_offset, y_start + y_step, z_default);
            set_site(2, x_default + x_offset, y_start, z_default);
            set_site(3, x_default + x_offset, y_start, z_up);
            wait_all_reach();

            set_site(3, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
    }
}

/*
  - go forward (moves ~40mm/step)
  - blocking function
  - parameter step steps wanted to go
   ---------------------------------------------------------------------------*/
void step_forward(unsigned int step)
{
    move_speed = leg_move_speed;
    while (step-- > 0)
    {
        if (site_now[2][1] == y_start)
        {
            set_site(3, x_default + x_offset, y_start, z_default);
            //leg 2&1 move
            set_site(2, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(2, x_default + x_offset, (y_start + 2 * y_step) * left_speed, z_up);
            wait_all_reach();
            set_site(2, x_default + x_offset, (y_start + 2 * y_step) * left_speed, z_default + 7);
            wait_all_reach();

            move_speed = body_move_speed;

            set_site(0, x_default + x_offset, y_start, z_default);
            set_site(1, x_default + x_offset, (y_start + 2 * y_step) * right_speed, z_default);
            set_site(2, x_default - x_offset, y_start + y_step, z_default);
            set_site(3, x_default - x_offset, y_start + y_step, z_default);
            wait_all_reach();

            move_speed = leg_move_speed;

            set_site(1, x_default + x_offset, (y_start + 2 * y_step) * right_speed, z_up);
            wait_all_reach();
            set_site(1, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(1, x_default + x_offset, y_start, z_default + 7);
            wait_all_reach();
        }
        else
        {
            set_site(1, x_default + x_offset, y_start, z_default);
            //leg 0&3 move
            set_site(0, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(0, x_default + x_offset, (y_start + 2 * y_step) * right_speed, z_up);
            wait_all_reach();
            set_site(0, x_default + x_offset, (y_start + 2 * y_step) * right_speed, z_default + 7);
            wait_all_reach();

            move_speed = body_move_speed;

            set_site(0, x_default - x_offset, y_start + y_step, z_default);
            set_site(1, x_default - x_offset, y_start + y_step, z_default);
            set_site(2, x_default + x_offset, y_start, z_default);
            set_site(3, x_default + x_offset, (y_start + 2 * y_step) * left_speed, z_default);
            wait_all_reach();

            move_speed = leg_move_speed;

            set_site(3, x_default + x_offset, (y_start + 2 * y_step) * left_speed, z_up);
            wait_all_reach();
            set_site(3, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(3, x_default + x_offset, y_start, z_default + 7);
            wait_all_reach();
        }
    }
}

/*
  - go back
  - blocking function
  - parameter step steps wanted to go
   ---------------------------------------------------------------------------*/
void step_back(unsigned int step)
{
    move_speed = leg_move_speed;
    while (step-- > 0)
    {
        if (site_now[3][1] == y_start)
        {
            //leg 3&0 move
            set_site(3, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(3, x_default + x_offset, y_start + 2 * y_step, z_up);
            wait_all_reach();
            set_site(3, x_default + x_offset, y_start + 2 * y_step, z_default);
            wait_all_reach();

            move_speed = body_move_speed;

            set_site(0, x_default + x_offset, y_start + 2 * y_step, z_default);
            set_site(1, x_default + x_offset, y_start, z_default);
            set_site(2, x_default - x_offset, y_start + y_step, z_default);
            set_site(3, x_default - x_offset, y_start + y_step, z_default);
            wait_all_reach();

            move_speed = leg_move_speed;

            set_site(0, x_default + x_offset, y_start + 2 * y_step, z_up);
            wait_all_reach();
            set_site(0, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(0, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
        else
        {
            //leg 1&2 move
            set_site(1, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(1, x_default + x_offset, y_start + 2 * y_step, z_up);
            wait_all_reach();
            set_site(1, x_default + x_offset, y_start + 2 * y_step, z_default);
            wait_all_reach();

            move_speed = body_move_speed;

            set_site(0, x_default - x_offset, y_start + y_step, z_default);
            set_site(1, x_default - x_offset, y_start + y_step, z_default);
            set_site(2, x_default + x_offset, y_start + 2 * y_step, z_default);
            set_site(3, x_default + x_offset, y_start, z_default);
            wait_all_reach();

            move_speed = leg_move_speed;

            set_site(2, x_default + x_offset, y_start + 2 * y_step, z_up);
            wait_all_reach();
            set_site(2, x_default + x_offset, y_start, z_up);
            wait_all_reach();
            set_site(2, x_default + x_offset, y_start, z_default);
            wait_all_reach();
        }
    }
}


void body_left(int i)
{
    set_site(0, site_now[0][0] + i, KEEP, KEEP);
    set_site(1, site_now[1][0] + i, KEEP, KEEP);
    set_site(2, site_now[2][0] - i, KEEP, KEEP);
    set_site(3, site_now[3][0] - i, KEEP, KEEP);
    wait_all_reach();
}


void body_right(int i)
{
    set_site(0, site_now[0][0] - i, KEEP, KEEP);
    set_site(1, site_now[1][0] - i, KEEP, KEEP);
    set_site(2, site_now[2][0] + i, KEEP, KEEP);
    set_site(3, site_now[3][0] + i, KEEP, KEEP);
    wait_all_reach();
}


void hand_wave(int i)
{
    float x_tmp;
    float y_tmp;
    float z_tmp;
    move_speed = 1;
    if (site_now[3][1] == y_start)
    {
        body_right(15);
        x_tmp = site_now[2][0];
        y_tmp = site_now[2][1];
        z_tmp = site_now[2][2];
        move_speed = body_move_speed;
        for (int j = 0; j < i; j++)
        {
            set_site(2, turn_x1, turn_y1, 50);
            wait_all_reach();
            set_site(2, turn_x0, turn_y0, 50);
            wait_all_reach();
        }
        set_site(2, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_left(15);
    }
    else
    {
        body_left(15);
        x_tmp = site_now[0][0];
        y_tmp = site_now[0][1];
        z_tmp = site_now[0][2];
        move_speed = body_move_speed;
        for (int j = 0; j < i; j++)
        {
            set_site(0, turn_x1, turn_y1, 50);
            wait_all_reach();
            set_site(0, turn_x0, turn_y0, 50);
            wait_all_reach();
        }
        set_site(0, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_right(15);
    }
}


void hand_shake(int i)
{
    float x_tmp;
    float y_tmp;
    float z_tmp;

    move_speed = 1;
    
    if (site_now[3][1] == y_start)
    {
        body_right(15);
    
        x_tmp = site_now[2][0];
        y_tmp = site_now[2][1];
        z_tmp = site_now[2][2];
    
        move_speed = body_move_speed;
    
        for (int j = 0; j < i; j++)
        {
            set_site(2, x_default - 30, y_start + 2 * y_step, 55);
            wait_all_reach();
            set_site(2, x_default - 30, y_start + 2 * y_step, 10);
            wait_all_reach();
        }
        set_site(2, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
 
        move_speed = 1;
        body_left(15);
    }
    else
    {
        body_left(15);
    
        x_tmp = site_now[0][0];
        y_tmp = site_now[0][1];
        z_tmp = site_now[0][2];
    
        move_speed = body_move_speed;
    
        for (int j = 0; j < i; j++)
        {
            set_site(0, x_default - 30, y_start + 2 * y_step, 55);
            wait_all_reach();
            set_site(0, x_default - 30, y_start + 2 * y_step, 10);
            wait_all_reach();
        }
        set_site(0, x_tmp, y_tmp, z_tmp);
        wait_all_reach();
        move_speed = 1;
        body_right(15);
    }
}