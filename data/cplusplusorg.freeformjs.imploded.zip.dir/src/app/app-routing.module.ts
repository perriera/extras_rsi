import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { BooksByBjarneStroupstrupComponent } from './components/pages/books-by-bjarne-stroupstrup/books-by-bjarne-stroupstrup.component';
import { LanguageComponent } from './components/pages/language/language.component';
import { CStandards3Component } from './components/pages/c-standards-3/c-standards-3.component';
import { HomeComponent } from './components/home/home.component';
import { CppBooksComponent } from './components/pages/cpp-books/cpp-books.component';
import { AboutBjarneStroustrupComponent } from './components/pages/about-bjarne-stroustrup/about-bjarne-stroustrup.component';
import { LambdaExpressionsComponent } from './components/pages/lambda-expressions/lambda-expressions.component';
import { StandardizationComponent } from './components/pages/standardization/standardization.component';
import { SuccessComponent } from './components/demo/success/success.component';
import { TemplatesComponent } from './components/pages/templates/templates.component';
import { Books2Component } from './components/pages/books-2/books-2.component';
import { StandardLibraryComponent } from './components/pages/standard-library/standard-library.component';
import { PublicationsComponent } from './components/pages/publications/publications.component';
import { TechnicalReportsComponent } from './components/pages/technical-reports/technical-reports.component';
import { AboutCppComponent } from './components/about-cpp/about-cpp.component';
import { EvolutionComponent } from './components/pages/evolution/evolution.component';
import { AboutBjarneStroustrupInterviewsComponent } from './components/pages/about-bjarne-stroustrup-interviews/about-bjarne-stroustrup-interviews.component';
import { FrequentlyRequestedPapers1Component } from './components/pages/frequently-requested-papers-1/frequently-requested-papers-1.component';
import { CStandards2Component } from './components/pages/c-standards-2/c-standards-2.component';
import { Books8Component } from './components/pages/books-8/books-8.component';
import { ObjectsComponent } from './components/pages/objects/objects.component';
import { ObjectStorageComponent } from './components/pages/object-storage/object-storage.component';
import { ExceptionHandlingComponent } from './components/pages/exception-handling/exception-handling.component';
import { Books3Component } from './components/pages/books-3/books-3.component';
import { Books7Component } from './components/pages/books-7/books-7.component';
import { EtymologyComponent } from './components/pages/etymology/etymology.component';
import { FrequentlyRequestedPapersComponent } from './components/pages/frequently-requested-papers/frequently-requested-papers.component';
import { Books1Component } from './components/pages/books-1/books-1.component';
import { CompatibilityComponent } from './components/pages/compatibility/compatibility.component';
import { Books4Component } from './components/pages/books-4/books-4.component';
import { AboutCppStandardsCommitteeComponent } from './components/pages/about-cpp-standards-committee/about-cpp-standards-committee.component';
import { PhilosophyComponent } from './components/pages/philosophy/philosophy.component';
import { StroustrupWikiComponent } from './components/pages/stroustrup-wiki/stroustrup-wiki.component';
import { OperatorsAndOperatorOverloadingComponent } from './components/pages/operators-and-operator-overloading/operators-and-operator-overloading.component';
import { FrequentlyRequestedPapers2Component } from './components/pages/frequently-requested-papers-2/frequently-requested-papers-2.component';
import { CStandards1Component } from './components/pages/c-standards-1/c-standards-1.component';
import { CriticismComponent } from './components/pages/criticism/criticism.component';
import { OldHome2Component } from './components/demo/old-home-2/old-home-2.component';
import { FrequentlyRequestedPapers4Component } from './components/pages/frequently-requested-papers-4/frequently-requested-papers-4.component';
import { OldHomeComponent } from './components/demo/old-home/old-home.component';
import { PolymorphismComponent } from './components/pages/polymorphism/polymorphism.component';
import { AboutCppWikipediaComponent } from './components/pages/about-cpp-wikipedia/about-cpp-wikipedia.component';
import { Books5Component } from './components/pages/books-5/books-5.component';
import { HistoryComponent } from './components/pages/history/history.component';
import { Books6Component } from './components/pages/books-6/books-6.component';
import { FrequentlyRequestedPapers3Component } from './components/pages/frequently-requested-papers-3/frequently-requested-papers-3.component';
import { StroustrupHomeComponent } from './components/pages/stroustrup-home/stroustrup-home.component';

const appRoutes: Routes = [
	{ path: 'pages_books_by_bjarne_stroupstrup', component: BooksByBjarneStroupstrupComponent  },
	{ path: 'pages_language', component: LanguageComponent  },
	{ path: 'pages_c_standards_3', component: CStandards3Component  },
	{ path: '', component: HomeComponent  },
	{ path: 'pages_cpp_books', component: CppBooksComponent  },
	{ path: 'pages_about_bjarne_stroustrup', component: AboutBjarneStroustrupComponent  },
	{ path: 'pages_lambda_expressions', component: LambdaExpressionsComponent  },
	{ path: 'pages_standardization', component: StandardizationComponent  },
	{ path: 'demo_success', component: SuccessComponent  },
	{ path: 'pages_templates', component: TemplatesComponent  },
	{ path: 'pages_books_2', component: Books2Component  },
	{ path: 'pages_standard_library', component: StandardLibraryComponent  },
	{ path: 'pages_publications', component: PublicationsComponent  },
	{ path: 'pages_technical_reports', component: TechnicalReportsComponent  },
	{ path: 'about_cpp', component: AboutCppComponent  },
	{ path: 'pages_evolution', component: EvolutionComponent  },
	{ path: 'pages_about_bjarne_stroustrup_interviews', component: AboutBjarneStroustrupInterviewsComponent  },
	{ path: 'pages_frequently_requested_papers_1', component: FrequentlyRequestedPapers1Component  },
	{ path: 'pages_c_standards_2', component: CStandards2Component  },
	{ path: 'pages_books_8', component: Books8Component  },
	{ path: 'pages_objects', component: ObjectsComponent  },
	{ path: 'pages_object_storage', component: ObjectStorageComponent  },
	{ path: 'pages_exception_handling', component: ExceptionHandlingComponent  },
	{ path: 'pages_books_3', component: Books3Component  },
	{ path: 'pages_books_7', component: Books7Component  },
	{ path: 'pages_etymology', component: EtymologyComponent  },
	{ path: 'pages_frequently_requested_papers', component: FrequentlyRequestedPapersComponent  },
	{ path: 'pages_books_1', component: Books1Component  },
	{ path: 'pages_compatibility', component: CompatibilityComponent  },
	{ path: 'pages_books_4', component: Books4Component  },
	{ path: 'pages_about_cpp_standards_committee', component: AboutCppStandardsCommitteeComponent  },
	{ path: 'pages_philosophy', component: PhilosophyComponent  },
	{ path: 'pages_stroustrup_wiki', component: StroustrupWikiComponent  },
	{ path: 'pages_operators_and_operator_overloading', component: OperatorsAndOperatorOverloadingComponent  },
	{ path: 'pages_frequently_requested_papers_2', component: FrequentlyRequestedPapers2Component  },
	{ path: 'pages_c_standards_1', component: CStandards1Component  },
	{ path: 'pages_criticism', component: CriticismComponent  },
	{ path: 'demo_old_home_2', component: OldHome2Component  },
	{ path: 'pages_frequently_requested_papers_4', component: FrequentlyRequestedPapers4Component  },
	{ path: 'demo_old_home', component: OldHomeComponent  },
	{ path: 'pages_polymorphism', component: PolymorphismComponent  },
	{ path: 'pages_about_cpp_wikipedia', component: AboutCppWikipediaComponent  },
	{ path: 'pages_books_5', component: Books5Component  },
	{ path: 'pages_history', component: HistoryComponent  },
	{ path: 'pages_books_6', component: Books6Component  },
	{ path: 'pages_frequently_requested_papers_3', component: FrequentlyRequestedPapers3Component  },
	{ path: 'pages_stroustrup_home', component: StroustrupHomeComponent  }
];

@NgModule({
  imports: [
    RouterModule.forRoot(appRoutes),
  ],
  exports: [
    RouterModule,
  ],
})
export class AppRoutingModule { }

