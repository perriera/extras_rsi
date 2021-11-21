/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { StandardizationComponent } from './standardization.component';

describe('StandardizationComponent', () => {
  let component: StandardizationComponent;
  let fixture: ComponentFixture<StandardizationComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ StandardizationComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(StandardizationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

